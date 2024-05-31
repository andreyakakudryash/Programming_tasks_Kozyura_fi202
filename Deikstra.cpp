#include<iostream>
#include<vector>
#include<queue>


using namespace std;

struct Flight {
    int dist;
    int time;
    int cost;
    int length;
};

class Graph {
private:
    int num;
    vector<vector<Flight>> flights;
    int* pv;

public:
    Graph(int n) {
        num = n;
        flights.resize(n);


    }

    void addFlight(int start, int end, int time, int cost, int length) {
        flights[start].push_back({ end, time, cost, length});
        flights[end].push_back({ start, time, cost, length});
    }

    vector<int> findShortestPathByTime(int start, int end) {
        vector<int> time(num, numeric_limits<int>::max());
        vector<int> prev(num, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        time[start] = 0;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int curr = pq.top().second;
            pq.pop();

            if (curr == end) {
                break;
            }

            for (const auto& flight : flights[curr]) {
                int newTime = time[curr] + flight.time;
                if (newTime < time[flight.dist]) {
                    time[flight.dist] = newTime;
                    prev[flight.dist] = curr;
                    pq.push({ newTime, flight.dist });
                }
            }
        }

        vector<int> path;
        int curr = end;
        while (curr != -1) {
            path.push_back(curr);
            curr = prev[curr];
        }
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> findShortestPathByCost(int start, int end) {
        vector<int> cost(num, numeric_limits<int>::max());
        vector<int> prev(num, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        cost[start] = 0;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int curr = pq.top().second;
            pq.pop();

            if (curr == end) {
                break;
            }

            for (const auto& flight : flights[curr]) {
                int newCost = cost[curr] + flight.cost;
                if (newCost < cost[flight.dist]) {
                    cost[flight.dist] = newCost;
                    prev[flight.dist] = curr;
                    pq.push({ newCost, flight.dist });
                }
            }
        }

        vector<int> path;
        int curr = end;
        while (curr != -1) {
            path.push_back(curr);
            curr = prev[curr];
        }
        reverse(path.begin(), path.end());
        return path;
    }

   vector<int> Budget(int start, int budget) {
        vector<int> visited(num, 0);
        vector<int> dist(num, 10000);
        vector<int> can_effort;
        dist[start] = 0;
        int sum = 0;


        for (int i = 0; i < num; i++) {
            int min = 10000;
            int minindex = -1;

            for (int j = 0; j < num; j++) {
                if (visited[j] == 0 && (dist[j] < min)) {
                    min = dist[j];
                    minindex = j;
                }
            }

            if (minindex == -1) {
                break;
            }

            visited[minindex] = 1;

            for (const auto& flight : flights[minindex]) {
                sum = min + flight.cost;

                if (sum < dist[flight.dist]) {
                    dist[flight.dist] = sum;
                
                    if (sum > budget) {
                    continue;
                    }

                    else {
                        can_effort.push_back(flight.dist);
                    }
                }
            }
        }


        return can_effort;
    }


   vector<int>  Time(int start, int limit) {
       vector<int> visited(num, 0);
       vector<int> dist(num, 10000);
       vector<int> can_effort;

       dist[start] = 0;
       int sum = 0;


       for (int i = 0; i < num; i++) {
           int min = 10000;
           int minindex = -1;

           for (int j = 0; j < num; j++) {
               if (visited[j] == 0 && (dist[j] < min)) {
                   min = dist[j];
                   minindex = j;
               }
           }

           if (minindex == -1) {
               break;
           }

           visited[minindex] = 1;

           for (const auto& flight : flights[minindex]) {
               sum = min + flight.time;

               if (sum < dist[flight.dist]) {
                   dist[flight.dist] = sum;

                   if (sum > limit) {
                       continue;
                   }

                   else {
                       can_effort.push_back(flight.dist);
                   }
               }
           }
       }


       return can_effort;
   }


   void isPossible(int start, int end) {

       vector<int> visited(num, 0);
       vector<int> dist(num, 10000);
       vector<int> path;
       int step = 0;
       int current = end;

       dist[start] = 0;
       int sum = 0;

       pv = new int[end];

       for (int i = 0; i < end; i++) {
           pv[i] = -1;

       }

        dist[start] = 0;

        for (int i = 0; i < end; i++) {
            int min = 10000;
            int minindex = -1;

            for (int j = 0; j < end; j++) {
                if (visited[j] == 0 && (dist[j] < min)) {
                    min = dist[j];
                    minindex = j;
                }
            }

            if (minindex == -1) {
                break;
            }

            visited[minindex] = 1;

            for (const auto& flight : flights[minindex]) {
                sum = min + flight.length;
                if (sum < dist[flight.dist]) {
                    dist[flight.dist] = sum;
                    pv[flight.dist] = minindex;
                }
            }
        }

        path.push_back(current);

        while (pv[current] != -1) {
            current = pv[current];
            path.push_back(current);
            step += 1;

        }

        if (step <= 4) {

            reverse(path.begin(), path.end());

            cout << "Можно, данный путь выглядит следующим образом: ";

            for (int i : path) {

                cout << i << " ";

                if (i != end) {
                    cout << " <- ";
                }

            
            }
        }

        else {
            cout << "К сожалению, нельзя попасть из одного заданного вами города в другой не более чем с двумя или тремя пересадками";
        }

        
    }


};




int main() {


    setlocale(LC_ALL, "RU");

    Graph g(9);

    g.addFlight(0, 1, 2, 100, 1200);
    g.addFlight(0, 5, 1, 80, 1500);
    g.addFlight(0, 6, 1, 50, 900);
    g.addFlight(1, 3, 1, 120, 500);
    g.addFlight(3, 4, 2, 70, 1200);
    g.addFlight(5, 4, 2, 70, 1000);
    g.addFlight(6, 7, 2, 70, 1100);
    g.addFlight(7, 8, 2, 70, 1900);





    int choose;

    cout << "Выберите необходимую операцию: \n" << "1. Реализовать поиск по минимальному времени или минимальной стоимости " << endl;
    cout << "2. Реализовать поиск списка городов, в которые можно попасть из заданного, имея определенную сумму денег " << endl;
    cout << "3. Реализовать поиск списка городов, в которые можно попасть за определенное время " << endl;
    cout << "4. Определить, можно ли попасть из одного города в другой не более чем с двумя или тремя пересадками " << endl;

    cin >> choose;

    if (choose == 1) {
        cout << "1.По минимальному времени \n 2. По минимальной стоимости " << endl;
        int choose2;
        cin >> choose2;

        if (choose2 == 1) {
            vector<int> pathByTime = g.findShortestPathByTime(0, 4);
            cout << "Кратчайший путь по минимальному времени: ";
            for (int city : pathByTime) {
                cout << city << " ";
            }
            cout << endl;
        }

        else if (choose2 == 2) {
            vector<int> pathByCost = g.findShortestPathByCost(0, 4);
            cout << "Кратчайший путь по минимальной стоимости: ";
            for (int city : pathByCost) {
                cout << city << " ";
            }
            cout << endl;
        }
    }

    else if (choose == 2) {
        int budget, numCity;
        cout << "Введите свой бюджет: ";
        cin >> budget;

        cout << "Укажите город, из которого желаете осуществить поиск ";
        cin >> numCity;
        vector<int> cities = g.Budget(numCity, budget);

        for (int city : cities) {
            cout << city << " ";
        }

    }

    else if (choose == 3) {
        int time, numCity;
        cout << "Введите ограниченное время ";
        cin >> time;

        cout << "Укажите город, из которого желаете осуществить поиск ";

        cin >> numCity;

        vector<int> cities = g.Time(numCity, time);

        for (int city : cities) {
            cout << city << " ";
        }
    }

    else if (choose == 4) {
        int start, end;

        cout << "Введите город, из которого необходимо определить путь " << endl;
        cin >> start;

        cout << "Введите город, в который необходимо по итогу добраться " << endl;

        cin >> end;

        g.isPossible(start, end);

    }

    return 0;
}







//class Graph {
//private:
//    int countVertex = 6;
//    int countEdges = 9;
//    int sum = 0;
//    vector<vector<pair<int, int>>> graph;
//    int* pv;
//
//public:
//    Graph() {
//        graph.resize(countVertex);
//
//        pv = new int[countVertex];
//
//        for (int i = 0; i < countVertex; i++) {
//            pv[i] = -1;
//        }
//    }
//
//    void addEdge(int start, int end, int weight) {
//        graph[start].push_back({ end, weight });
//        graph[end].push_back({ start, weight });
//    }
//
//    vector<int> dj(int start) {
//        vector<int> dist(graph.size(), 10000);
//        vector<int> visited(graph.size(), 0);
//
//        dist[start] = 0;
//
//        for (int i = 0; i < graph.size(); i++) {
//            int min = 10000;
//            int minindex = -1;
//
//            for (int j = 0; j < graph.size(); j++) {
//                if (visited[j] == 0 && (dist[j] < min)) {
//                    min = dist[j];
//                    minindex = j;
//                }
//            }
//
//            if (minindex == -1) {
//                break;
//            }
//
//            visited[minindex] = 1;
//
//            for (const auto& pair : graph[minindex]) {
//                sum = min + pair.second;
//                if (sum < dist[pair.first]) {
//                    dist[pair.first] = sum;
//                    pv[pair.first] = minindex;
//                }
//            }
//        }
//
//        return dist;
//    }
//
//    void printShortestPath(int end) {
//
//
//        vector<int> path;
//        int current = end;
//        path.push_back(current);
//
//        while (pv[current] != -1) {
//            current = pv[current];
//            path.push_back(current);
//        }
//
//        cout << endl << "Shortest path: ";
//
//        for (int i : path) {
//
//            cout << i << " ";
//
//            if (i > 0) {
//                cout << " <- ";
//            }
//
//            
//        }
//    }
//
//    ~Graph() {
//        delete[]pv;
//    }
//
//};
//
//int main() {
//    setlocale(LC_ALL, "RU");
//
//    Graph g;
//
//    g.addEdge(0, 1, 7);
//    g.addEdge(0, 2, 9);
//    g.addEdge(0, 5, 14);
//    g.addEdge(1, 2, 10);
//    g.addEdge(1, 3, 15);
//    g.addEdge(2, 5, 2);
//    g.addEdge(2, 3, 11);
//    g.addEdge(3, 4, 6);
//    g.addEdge(5, 4, 9);
//
//
//
//    vector<int> dist = g.dj(0);
//
//    for (int i : dist) {
//        if (i < 10000) {
//            cout << i << " ";
//        }
//        else {
//            cout << "X ";
//        }
//    }
//
//    g.printShortestPath(4);
//
//
//    return 0;
//}




