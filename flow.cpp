/**
 * Title - Flow Free Game Solver.
 *
 * Copyright (C) 2011 Kentaro Imajo. All rights reserved.
 * Author: Kentaro Imajo (Twitter: imos)
 *
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>
#include <stack>
#include <vector>

using namespace std;

bool FLAGS_color = false;

class NumberLink {
 public:
	typedef char CellNumber;
	typedef short CellKey;
	typedef short CellPosition;
	typedef int Distance;
	Distance width_;
	Distance height_;

	NumberLink(const Distance width, const Distance height):
	    width_(width), height_(height), size_((CellKey)width * height),
	    cell_x_(size_), cell_y_(size_), table_(size_),
	    keys_(size_), mates_(size_), start_(size_ + 1),
	    connected_x_(size_), connected_y_(size_), memo_(size_) {}

	void Initialize() {
		for (CellKey cell_key = 0; cell_key < size_; cell_key++) {
			mates_[cell_key] = cell_key;
		}

		Distance x = 0, y = 0;
		CellKey cell_key = 0;
		while (true) {
			CellPosition position = (CellPosition)y * width_ + x;
			cell_x_[cell_key] = x;
			cell_y_[cell_key] = y;
			keys_[position] = cell_key;
			cell_key++;
			if (cell_key == size_) break;
			do {
				x--;
				y++;
				if (x < 0) {
					x = y;
					y = 0;
				}
			} while (x < 0 || width_ <= x || y < 0 || height_ <= y);
		}

		for (CellKey i = 0; i < size_; i++) {
			Distance x = cell_x_[i], y = cell_y_[i];
			start_[i] = 0 < y ? GetCellKey(x, y - 1) :
			                    (0 < x ? GetCellKey(x - 1, y) : 0);
		}
		start_[size_] = size_;
	}

	CellNumber& Cell(const Distance x, const Distance y)
	    { return table_[GetCellKey(x, y)]; }
	CellKey GetCellKey(const Distance x, const Distance y) const
	    { return keys_[(CellPosition)y * width_ + x]; }

	double Solve(const CellKey cell_key = 0) {
		if (cell_key == 0) solved_ = false;
		if (0 < cell_key) {
			for (CellKey hidden = start_[cell_key - 1];
			    hidden < start_[cell_key]; hidden++) {
				if (table_[hidden] == 0) {
					if (mates_[hidden] != -1 && mates_[hidden] != hidden) return 0.0;
				} else {
					if (mates_[hidden] == hidden) return 0.0;
				}
			}
		}
		if (cell_key == size_) {
			if (!solved_) {
				Print();
				solved_ = true;
			}
			return 1.0;
		}
		
		const vector<CellKey> mate_tuple(mates_.begin() + start_[cell_key],
		                                 mates_.begin() + cell_key);
		const Hash mate_hash = GetHash(mate_tuple);
		if (!memo_[cell_key].count(mate_hash)) {
			memo_[cell_key][mate_hash] = Connect(cell_key);
		}
		return memo_[cell_key][mate_hash];
	}

	double Connect(const CellKey cell_key) {
		double solution_count = 0.0;
		Distance x = cell_x_[cell_key], y = cell_y_[cell_key];
		CellKey left_cell_key = -1, up_cell_key = -1;
		if (0 < x) left_cell_key = GetCellKey(x - 1, y);
		if (0 < y) up_cell_key = GetCellKey(x, y - 1);
		size_t revert_point = mate_stack_.size();
		solution_count += Solve(cell_key + 1);
		if (0 <= up_cell_key) {
			if (UniteMates(cell_key, up_cell_key)) {
				connected_y_[cell_key] = true;
				solution_count += Solve(cell_key + 1);
				connected_y_[cell_key] = false;
			}
			RevertMates(revert_point);
		}
		if (0 <= left_cell_key) {
			if (UniteMates(cell_key, left_cell_key)) {
				connected_x_[cell_key] = true;
				solution_count += Solve(cell_key + 1);
				if (0 <= up_cell_key) {
					if (UniteMates(cell_key, up_cell_key)) {
						connected_y_[cell_key] = true;
						solution_count += Solve(cell_key + 1);
						connected_y_[cell_key] = false;
					}
				}
				connected_x_[cell_key] = false;
			}
			RevertMates(revert_point);
		}
		return solution_count;
	}

	void Print() {
		string table[width_][height_];

		for (int i = 0; i < width_; ++i)
		{
			for (int j = 0; j < height_; ++j)
			{
				table[i][j]=" ";
			}
		}



		for (Distance y = 0; y <= height_; y++) 
		{
			
			for (Distance x = 0; x < width_; x++)
			 {
				printf(FLAGS_color ? "\x1b[32m+\x1b[0m" : "+");
				printf((y % height_ == 0) ?
				       (FLAGS_color ? "\x1b[32m---\x1b[0m" : "---") :
				       (connected_y_[GetCellKey(x, y)] ? " # " : "   "));
						if (y%height_ !=0)
						{
							if (connected_y_[GetCellKey(x, y)] )
							{
								table[x][y]=" ";
							}
						}
				// printf("%d ", table_[GetCellKey(x,y)] );
			}
			
			printf("\n");
			puts(FLAGS_color ? "\x1b[32m+\x1b[0m" : "+");
			if (height_ <= y) break;
			for (Distance x = 0; x < width_; x++) 
			{
				
				printf(x ? (connected_x_[GetCellKey(x, y)] ? "#" : " ") :
				       (FLAGS_color ? "\x1b[32m|\x1b[0m" : "|"));
				       	if (x)
				       	{
				       		if (connected_x_[GetCellKey(x, y)])
				       		{
				       			table[x][y]="#";
				       		}
				       	}
				       	
				if (table_[GetCellKey(x, y)]) 
				{
					printf("%03d", table_[GetCellKey(x, y)]);
					int str = table_[GetCellKey(x, y)];
					table[x][y] = table_[GetCellKey(x, y)]+'0';
				} 
				else 
				{
					printf(connected_x_[GetCellKey(x, y)] ? "#" : " ");
					if (connected_x_[GetCellKey(x, y)])
					{
						table[x][y] = "#"; 
					}
					
					printf(mates_[GetCellKey(x, y)] == GetCellKey(x, y) ? " " : "#");
					if (mates_[GetCellKey(x, y)] != GetCellKey(x, y))
					{
						table[x][y]="#";
					}
					printf((x + 1 < width_ && connected_x_[GetCellKey(x + 1, y)])
					       ? "@" : " ");
					if ((x + 1 < width_ && connected_x_[GetCellKey(x + 1, y)]))
					{
						table[x][y]="#";
					}
				}
			}
			puts(FLAGS_color ? "\x1b[32m|\x1b[0m" : "|");
		}


		cout<<endl;
		cout<<endl;
		for (int i = 0; i < width_; ++i)
		{
			for (int j = 0; j < height_; ++j)
			{
				cout<<table[j][i]<<" ";
			}
			cout<<endl;
		}
	}

 private:
	typedef pair<long long, long long> Hash;
	CellKey size_;
	stack< pair<CellKey, CellKey> > mate_stack_;
	vector<Distance> cell_x_, cell_y_;
	vector<CellNumber> table_;
	vector<CellKey> keys_, mates_, start_;
	vector<bool> connected_x_, connected_y_;
	vector< map<Hash, double> > memo_;
	bool solved_;

	Hash GetHash(const vector<CellKey> &cell_keys) {
		unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
		for (int i = 0; i < (int)cell_keys.size(); i++) {
			unsigned int t = (x ^ (x << 11)); x = y; y = z; z = w;
			w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)) + (unsigned int)cell_keys[i];
		}
		Hash h;
		h.first = ((unsigned long long)x << 32) | y;
		h.second = ((unsigned long long)z << 32) | w;
		return h;
	}

	int ChangeMates(const CellKey cell_key, const CellKey cell_value) {
		int last_stack_size = mate_stack_.size();
		CellKey last_value = mates_[cell_key];
		if (last_value != cell_value) {
			mate_stack_.push(make_pair(cell_key, last_value));
			mates_[cell_key] = cell_value;
		}
		return last_stack_size;
	}

	void RevertMates(const size_t stack_size) {
		for (; stack_size < mate_stack_.size(); mate_stack_.pop())
		    mates_[mate_stack_.top().first] = mate_stack_.top().second;
	}

	bool UniteMates(const CellKey cell_key1, const CellKey cell_key2) {
		CellKey end1 = mates_[cell_key1], end2 = mates_[cell_key2];
		if (end1 == -1 || end2 == -1) return false;
		if (cell_key1 == end2 && cell_key2 == end1) return false;
		ChangeMates(cell_key1, -1);
		ChangeMates(cell_key2, -1);
		ChangeMates(end1, end2);
		ChangeMates(end2, end1);
		if (mates_[cell_key1] == -1 && 0 < table_[cell_key1]) return false;
		if (mates_[cell_key2] == -1 && 0 < table_[cell_key2]) return false;
		if (0 < table_[end1] && 0 < table_[end2] &&
		    table_[end1] != table_[end2]) return false;
		return true;
	}
};

int main(int argc, char **argv) {
	//ParseArguments(&argc, argv);
	int width=5, height=5;
	// while (2 == scanf("%d%d", &width, &height) && width && height) {
	// 	NumberLink nl((int)width, (int)height);
	// 	nl.Initialize();
	// 	for (int y = 0; y < nl.height_; y++) {
	// 		for (int x = 0; x < nl.width_; x++) {
	// 			int value;
	// 			scanf("%d", &value);
	// 			nl.Cell(x, y) = value;
	// 		}
	// 	}
	// 	double solution_count = nl.Solve();
	// 	printf("# of solutions: ");
	// 	if (solution_count < 1e13) {
	// 		printf("%.0f\n", solution_count);
	// 	} else {
	// 		printf("%.13e\n", solution_count);
	// 	}
	// }
	NumberLink nl((int)width, (int)height);
	nl.Initialize();
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			nl.Cell(j,i) = 0;
		}
	}
	nl.Cell(0,0) = nl.Cell(1,4) = 1;
	nl.Cell(2,0) = nl.Cell(1,3) = 2;
	nl.Cell(2,1) = nl.Cell(2,4) = 3;
	nl.Cell(4,0) = nl.Cell(3,3) = 4;
	nl.Cell(4,1) = nl.Cell(3,4) = 5;
	double solution_count = nl.Solve();
	return 0;
}
