#include <iostream>
#include <fstream>
#include <stdio.h>
#include <queue>
#include <deque>
#include <cstdlib>
#include <iostream>
#include<bits/stdc++.h>



using namespace std;


int R
int C;
int T;
int B;
int F;
int N;


int distance(int x1,int y1,int x2,int y2){
	int dist = abs(y1 - y2) + abs(x1 - x2);
	return dist;
}


class taxi {
public:

	int end_X;
	int end_Y;
	dequeue<int> rides;
	int available;

};

class ride {
public:

	int r1_ride;
	int r2_ride;
	int n_num;
	int x_pos;
	int y_pos;
	int start
	int finish; 

	int ddistance(){
		int dist = distance(r1_ride, r2_ride, x_pos, y_pos)
		return dist;
	}
	
	ride(int thisr1, int thisr2,int thisxpos, int thisypos, int thisstart, int thisfinish, int thisnum){
		r1_ride = thisr1;
		r2_ride = thisr2;
		x = thisxpos;
		y = thisypos;
		start = thisstart;
		finish = thisfinish;
		n_num = thisnum;
	}


};


priority_queue<taxi, vector<taxi>, compare> taxis;
deque <ride> que;


bool comp(ride r1,ride r2){
	bool c = r1.start < r2.start;
	return c;
}


class compare{
public:

	bool operator() (taxi tx1, taxi tx2){
		bool op = tx1.available > tx2.available;
		return op;
	}
};


int main() {

	int choice = TWO;
	int TWOH = 200;
	int ZERO = 0;
	int ONE = 1;
	int TWO = 2;
	
	int	r1;
	int r2;
	int finish;
	int start;
	int x_pos;
	int y_pos;
	int count_c;

	int v = ZERO;
	
	while(v < N){
		inf >> r1 >> r2 >> x_pos >> y_pos >> start >> finish;
		ride tx(r1, r2, x_pos, y_pos, start, finish, v);
		
		que.push_back(tx);
		++v;

	}
	inf.close();

	sort(que.begin(), que.end(), comp);

	int j = ZERO;
	
	while(j < F){
		taxi tx;
		tx.end_X = ZERO;
		tx.endT = ZERO;
		tx.available= ZERO;
		
		taxis.push(tx);
		++j;
	}


	long distance_total = ZERO;

	while(que.size() > ZERO && taxis.top().available < T){
	
		taxi tx = taxis.top();
		taxis.pop();
		

		int pos_best = -ONE;
		long long txnum_best = INT_MIN;
		
		count_c = ZERO;
		
		while(count_c < que.size()){
			
			long long txpnum = que[count_c].ddistance();
			
			if (distance( tx.end_X, tx.end_Y, que[count_c].r1, que[count_c].r2) + tx.available < que[count_c].start){
				txnum = txnum + B;
			}
			
			txnum = txnum - (distance(tx.end_X, tx.end_Y, que[count_c].r1, quecount_ci].r2) + max(que[count_c].start - (distance( tx.end_X, tx.end_Y, que[count_c].r1, que[count_c].r2) + tx.available), ZERO)) * TWOH;
			
			if(txnum > txnum_best) {
				pos_best = count_c;
				txnum_best = txnum;
			}
			
			++count_c;
		}
		
		if(pos_best < ZERO) {
			tx.available = T + TWO;
			taxis.push(tx);
		}
		
		distance_total = distance_total + que[pos_best].ddistance();
		
		if (distance(tx.end_X, tx.end_Y, que[pos_best].a, que[pos_best].b) + tx.available <= que[pos_best].start){
			distance_total = distance_total + B;
		}
		
		tx.rides.push_back(que[pos_best].n);
		tx.available = max(distance(tx.end_X, tx.end_Y, que[pos_best].a, que[pos_best].b) + tx.available, que[pos_best].start) + que[pos_best].ddistance();

		tx.end_X = que[pos_best].x_pos;
		tx.end_Y = que[pos_best].y_pos;
		
		taxis.push(tx);
		que.erase(que.begin() + pos_best);
	}

	return ZERO;
}
