#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include <algorithm>
using namespace std;

void parse(string gamestr, int& gx, int& gy, int& goalx, int& goaly, string& initgrid)
{
    for (int i = 0; i < gamestr.size(); i++)
        if (gamestr[i] >= '0' && gamestr[i] <= '9')
            gamestr[i] -= '0';

    gx = gamestr[0];
    gy = gamestr[2];
    goalx = gamestr[4];
    goaly = gamestr[6];

   // cout<<gx<<endl<<gy<<endl<<goalx<<endl<<goaly;

    vector<int> gamegrid(gx*gy, -1);
    istringstream iss(gamestr.substr(8));
    string sz_curblock;
    int blockid = 0;
    while(getline(iss, sz_curblock, ','))
    {
        for (int x = 0; x < sz_curblock[2]; x++)
            for (int y = 0; y < sz_curblock[3]; y++)
                gamegrid[(sz_curblock[1] + y) * gx + sz_curblock[0] + x] = blockid;
        blockid++;
    }
    initgrid = "";
    for (int i = 0; i < gamegrid.size(); i++)
        initgrid += ((char)gamegrid[i] + '0');
    //cout<<"initgrid = "<<initgrid;
    //exit(1);
}

bool issolved(int& gx, int& gy, int& goalx, int& goaly, string& curgrid)
{
    if (goaly == 0)
        return (curgrid[goalx] == curgrid[gx + goalx] && curgrid[goalx] >= '0');
    else if (goalx == 0)
        return (curgrid[goaly * gx] == curgrid[goaly * gx + 1] && curgrid[goaly * gx] >= '0');
    else if (goalx > goaly)
        return (curgrid[goaly * gx + goalx] == curgrid[goaly * gx + goalx - 1] &&
                curgrid[goaly * gx + goalx] >= '0');
    else if (goalx < goaly)
        return (curgrid[goaly * gx + goalx] == curgrid[(goaly - 1) * gx + goalx] &&
                curgrid[goaly * gx + goalx] >= '0');
    else
        return false;
}

void printsoln(int& gx, int& gy, vector<string>& moves)
{
    for (int i = 1; i < moves.size(); i++)
    {
        cout << "Move #" << i << endl;
        for (int x = 0; x < gx; x++)
        {
            for (int y = 0; y < gy; y++)
                cout << moves[i-1][x * gy + y] << " ";
            cout << endl;
        }
        system("PAUSE");
        cout << endl;
    }
    cout << "Total moves: " << moves.size() << endl;
}

void findmoves(int& gx, int& gy, string& curgrid, vector<string>& nextgrids)
{
    for (int i = 0; i < curgrid.size(); i++)
    {
        if (curgrid[i] >= '0') continue;
        vector<pair<int, int> > paths;
        paths.push_back(make_pair(-1, ((int)(i/gx)) * gx));
        paths.push_back(make_pair(1, ((int)(i/gx + 1)) * gx - 1));
        paths.push_back(make_pair(-gx, i%gx));
        paths.push_back(make_pair(gx, (gy - 1)*gx + i%gx));
       
        cout<<endl<<paths.size();

        for (int j = 0; j < paths.size(); j++)
        {
            int x, c;
            for (x = i; (paths[j].first < 0) ? (x >= paths[j].second) : (x <= paths[j].second); x += paths[j].first)
                if (curgrid[x] >= '0') break;
            if (x == paths[j].second) continue;
            if (curgrid[x] != curgrid[x + paths[j].first]) continue;

            string nextgrid = curgrid;
            for (c = x; (paths[j].first < 0) ? (c >= paths[j].second) : (c <= paths[j].second); c += paths[j].first)
            {
                if (curgrid[c] != curgrid[x]) break;
                nextgrid[i + (c-x)] = nextgrid[c];
                nextgrid[c] = '0'-1;
            }
            nextgrids.push_back(nextgrid);
        }
    }
}

void solve(string gamestr)
{
    int gx, gy, goalx, goaly;
    string initgrid;
    parse(gamestr, gx, gy, goalx, goaly, initgrid);

    map<string, pair<string, int> > seen;
    queue<pair<string, int> > squeue;
    squeue.push(make_pair(initgrid, 0));
    string solvedgrid;
    while(!squeue.empty())
    {
        pair<string, int> cur = squeue.front();
        squeue.pop();
        if (issolved(gx, gy, goalx, goaly, cur.first))
        {
            solvedgrid = cur.first;
            break;
        }
       // cout<<cur.first<<endl;
       // exit(1);
        vector<string> nextgrids;
        findmoves(gx, gy, cur.first, nextgrids);
        exit(1);
        for (int i = 0; i < nextgrids.size(); i++)
        {
            if (seen.find(nextgrids[i]) != seen.end())
            {
                if (seen[nextgrids[i]].second > cur.second)
                    seen[nextgrids[i]] = make_pair(cur.first, cur.second+1);
            }
            else
            {
                squeue.push(make_pair(nextgrids[i], cur.second+1));
                seen[nextgrids[i]] = make_pair(cur.first, cur.second+1);
            }
        }
    }
    cout << "Solved: " << solvedgrid << endl;
    cout << "Total states explored: " << seen.size() << endl;
    cout << "=====================" << endl << endl;

    vector<string> moves;
    do {
        moves.push_back(solvedgrid);
        solvedgrid = seen[solvedgrid].first;
    } while(seen[solvedgrid].second > 1);
    moves.push_back(solvedgrid);
    reverse(moves.begin(), moves.end());
    printsoln(gx, gy, moves);
}

int main()
{
    solve("6,6,5,2,0031,0112,0321,1121,1412,2221g,2312,2521,3012,4013,4421,4521,5013");
    return 0;
}