// CompetitiveProgrammingTemplate.cpp
#include <bits/stdc++.h>
using namespace std;

// =======================
// TwoSAT Algorithm
// =======================
namespace TwoSAT {
    class TwoSAT {
    private:
        int n;
        vector<vector<int>> adj;
        vector<vector<int>> radj;
        vector<bool> visited;
        vector<int> order, sccId;
        int sccCounter;

        void dfs(int here) {
            visited[here] = true;
            for(int there : adj[here])
                if(!visited[there])
                    dfs(there);
            order.push_back(here);
        }

        void reverseDfs(int here) {
            visited[here] = true;
            sccId[here] = sccCounter;
            for(int there : radj[here])
                if(!visited[there])
                    reverseDfs(there);
        }

    public:
        TwoSAT(int _n) : n(_n) {
            adj.resize(2*n);
            radj.resize(2*n);
        }

        int neg(int x) {
            return x >= n ? x-n : x+n;
        }

        void addClause(int x, int y) {
            adj[neg(x)].push_back(y);
            adj[neg(y)].push_back(x);
            radj[y].push_back(neg(x));
            radj[x].push_back(neg(y));
        }

        vector<bool> solve() {
            visited = vector<bool>(2*n, false);
            order.clear();

            for(int i = 0; i < 2*n; i++)
                if(!visited[i])
                    dfs(i);

            reverse(order.begin(), order.end());
            visited = vector<bool>(2*n, false);
            sccId = vector<int>(2*n, -1);
            sccCounter = 0;

            for(int x : order)
                if(!visited[x]) {
                    reverseDfs(x);
                    sccCounter++;
                }

            for(int i = 0; i < n; i++)
                if(sccId[i] == sccId[i+n])
                    return vector<bool>();

            vector<bool> result(n);
            for(int i = 0; i < n; i++)
                result[i] = sccId[i] > sccId[i+n];
            return result;
        }
    };

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, m;
        cin >> n >> m;

        TwoSAT sat(n);

        while(m--) {
            int a, b;
            cin >> a >> b;
            if(a > 0) a--;
            else a = (-a-1) + n;
            if(b > 0) b--;
            else b = (-b-1) + n;
            sat.addClause(a, b);
        }

        vector<bool> result = sat.solve();

        if(result.empty()) {
            cout << "0\n";
        } else {
            cout << "1\n";
            for(int i = 0; i < n; i++)
                cout << result[i] << " ";
            cout << "\n";
        }
    }
}

// =======================
// Bellman-Ford Algorithm
// =======================
namespace BellmanFord {
    struct Edge {
        int from, to, cost;
    };

    const int MAX = 501;
    vector<Edge> edges;
    long long dist_arr[MAX];
    int N, M;

    bool bellmanFord(int start) {
        fill(dist_arr, dist_arr + MAX, 1e18);
        dist_arr[start] = 0;

        for(int i = 1; i <= N; i++) {
            for(auto &edge : edges) {
                if(dist_arr[edge.from] != 1e18 && 
                   dist_arr[edge.to] > dist_arr[edge.from] + edge.cost) {
                    dist_arr[edge.to] = dist_arr[edge.from] + edge.cost;
                    if(i == N) return true;
                }
            }
        }
        return false;
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> N >> M;

        for(int i = 0; i < M; i++) {
            int from, to, cost;
            cin >> from >> to >> cost;
            edges.push_back({from, to, cost});
        }

        bool hasCycle = bellmanFord(1);

        if(hasCycle) cout << "Negative cycle exists\n";
        else {
            for(int i = 1; i <= N; i++) {
                if(dist_arr[i] == 1e18) cout << "INF\n";
                else cout << dist_arr[i] << '\n';
            }
        }
    }
}

// =======================
// Breadth-First Search (BFS)
// =======================
namespace BFS {
    const int MAX = 1001;
    vector<int> graph[MAX];
    bool visited[MAX];
    int n, m;

    void bfs(int start) {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while(!q.empty()) {
            int cur = q.front();
            q.pop();
            cout << cur << ' ';

            for(int next : graph[cur]) {
                if(!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        for(int i = 1; i <= n; i++) {
            sort(graph[i].begin(), graph[i].end());
        }

        bfs(1);
        cout << "\n";
    }
}

// =======================
// Binary Search
// =======================
namespace BinarySearch {
    // Iterative Binary Search
    int binarySearch(vector<int> &arr, int target)
    {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target)
            {
                return mid;
            }
            else if (arr[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return -1;
    }

    // Recursive Binary Search
    int binarySearchRecursive(vector<int> &arr, int target, int left, int right)
    {
        if (left > right)
            return -1;

        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            return binarySearchRecursive(arr, target, mid + 1, right);
        }
        else
        {
            return binarySearchRecursive(arr, target, left, mid - 1);
        }
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, m;
        cout << "배열의 크기를 입력하세요: ";
        cin >> n;

        vector<int> arr(n);
        cout << "정렬된 배열을 입력하세요: ";
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        cout << "찾을 원소의 개수를 입력하세요: ";
        cin >> m;

        cout << "찾을 원소들을 입력하세요: \n";
        for (int i = 0; i < m; i++)
        {
            int target;
            cin >> target;

            int result1 = binarySearch(arr, target);
            cout << target << "의 일반 이분 탐색 결과: ";
            if (result1 != -1)
            {
                cout << result1 << "번 인덱스\n";
            }
            else
            {
                cout << "찾지 못함\n";
            }

            int result2 = binarySearchRecursive(arr, target, 0, n - 1);
            cout << target << "의 재귀 이분 탐색 결과: ";
            if (result2 != -1)
            {
                cout << result2 << "번 인덱스\n";
            }
            else
            {
                cout << "찾지 못함\n";
            }

            auto lower = lower_bound(arr.begin(), arr.end(), target);
            auto upper = upper_bound(arr.begin(), arr.end(), target);
            cout << target << "의 개수: " << upper - lower << "\n";
            cout << "----------------\n";
        }
    }
}

// =======================
// Bipartite Matching
// =======================
namespace BipartiteMatching {
    const int MAX = 1001;
    vector<int> graph[MAX];
    int matched[MAX];
    bool visited[MAX];

    bool dfs(int cur) {
        if (visited[cur]) return false;
        visited[cur] = true;

        for (int next : graph[cur]) {
            if (matched[next] == -1 || dfs(matched[next])) {
                matched[next] = cur;
                return true;
            }
        }
        return false;
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, m, k;
        cin >> n >> m >> k;

        for (int i = 1; i <= n; i++) {
            int cnt;
            cin >> cnt;
            while (cnt--) {
                int work;
                cin >> work;
                graph[i].push_back(work);
            }
        }

        fill(matched, matched + MAX, -1);

        int match = 0;
        for (int i = 1; i <= n; i++) {
            fill(visited, visited + MAX, false);
            if (dfs(i)) match++;
        }

        for (int i = 1; i <= n && match < k; i++) {
            fill(visited, visited + MAX, false);
            if (dfs(i)) match++;
        }

        cout << match << '\n';
    }
}

// =======================
// Bitmask and Bit Operations
// =======================
namespace Bitmask {
    class BitSet {
    private:
        int bits;

    public:
        BitSet() : bits(0) {}

        void add(int x) {
            bits |= (1 << x);
        }

        void remove(int x) {
            bits &= ~(1 << x);
        }

        void toggle(int x) {
            bits ^= (1 << x);
        }

        bool contains(int x) {
            return bits & (1 << x);
        }

        int count() {
            return __builtin_popcount(bits);
        }

        void print() {
            for(int i = 0; i < 32; i++) {
                if(contains(i)) cout << i << " ";
            }
            cout << "\n";
        }

        void printAllSubsets() {
            for(int subset = bits; subset; subset = (subset-1) & bits) {
                for(int i = 0; i < 32; i++) {
                    if(subset & (1 << i)) cout << i << " ";
                }
                cout << "\n";
            }
        }

        void unionSet(const BitSet& other) {
            bits |= other.bits;
        }

        void intersectSet(const BitSet& other) {
            bits &= other.bits;
        }

        void differenceSet(const BitSet& other) {
            bits &= ~other.bits;
        }

        int getMin() {
            if(bits == 0) return -1;
            return __builtin_ctz(bits);
        }

        int getMax() {
            if(bits == 0) return -1;
            return 31 - __builtin_clz(bits);
        }
    };

    class BitUtils {
    public:
        static int lsb(int x) {
            return x & -x;
        }

        static int turnOffLsb(int x) {
            return x & (x-1);
        }

        static int turnOnLsb(int x) {
            return x | (x+1);
        }

        static int countBits(int x) {
            return __builtin_popcount(x);
        }

        static int lowestBitPos(int x) {
            return __builtin_ctz(x);
        }

        static int highestBitPos(int x) {
            return 31 - __builtin_clz(x);
        }
    };

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        BitSet set;
        set.add(1);
        set.add(3);
        set.add(5);

        cout << "Current set: ";
        set.print();
        cout << "Contains 3? " << set.contains(3) << "\n";
        cout << "Element count: " << set.count() << "\n";

        set.remove(3);
        cout << "After removing 3: ";
        set.print();

        // Example usage of BitUtils
        int n;
        cin >> n;
        // Additional code can be added here as needed
    }
}

// =======================
// Boyer-Moore String Matching
// =======================
namespace BoyerMoore {
    const int NO_OF_CHARS = 256;

    void badCharHeuristic(string pattern, int badchar[NO_OF_CHARS]) {
        int m = pattern.length();

        for(int i = 0; i < NO_OF_CHARS; i++) {
            badchar[i] = -1;
        }

        for(int i = 0; i < m; i++) {
            badchar[(int)pattern[i]] = i;
        }
    }

    vector<int> boyerMooreSearch(string text, string pattern) {
        vector<int> ans;
        int n = text.length();
        int m = pattern.length();

        int badchar[NO_OF_CHARS];
        badCharHeuristic(pattern, badchar);

        int s = 0;
        while(s <= (n - m)) {
            int j = m - 1;

            while(j >= 0 && pattern[j] == text[s + j]) {
                j--;
            }

            if(j < 0) {
                ans.push_back(s);
                s += (s + m < n) ? m - badchar[text[s + m]] : 1;
            }
            else {
                s += max(1, j - badchar[text[s + j]]);
            }
        }
        return ans;
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        string text, pattern;
        getline(cin, text);
        getline(cin, pattern);

        vector<int> result = boyerMooreSearch(text, pattern);
        cout << "Boyer-Moore: " << result.size() << '\n';
        for(int pos : result) {
            cout << pos + 1 << ' ';
        }
        cout << '\n';
    }
}

// =======================
// Convex Hull and Rotating Calipers
// =======================
namespace ComputationalGeometry {
    typedef pair<long long, long long> Point;

    long long ccw(const Point& p1, const Point& p2, const Point& p3) {
        long long ret = (p2.first - p1.first) * (p3.second - p1.second) - 
                        (p3.first - p1.first) * (p2.second - p1.second);
        if(ret > 0) return 1;
        if(ret < 0) return -1;
        return 0;
    }

    bool isIntersect(const pair<Point, Point>& l1, const pair<Point, Point>& l2) {
        Point p1 = l1.first, p2 = l1.second, p3 = l2.first, p4 = l2.second;

        long long ccw1 = ccw(p1, p2, p3) * ccw(p1, p2, p4);
        long long ccw2 = ccw(p3, p4, p1) * ccw(p3, p4, p2);

        if(ccw1 == 0 && ccw2 == 0) {
            if(p1 > p2) swap(p1, p2);
            if(p3 > p4) swap(p3, p4);
            return !(p2 < p3 || p4 < p1);
        }

        return ccw1 <= 0 && ccw2 <= 0;
    }

    pair<double,double> intersection(const pair<Point, Point>& l1, const pair<Point, Point>& l2) {
        double x1 = l1.first.first, y1 = l1.first.second;
        double x2 = l1.second.first, y2 = l1.second.second;
        double x3 = l2.first.first, y3 = l2.first.second;
        double x4 = l2.second.first, y4 = l2.second.second;

        double px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) /
                    ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
        double py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) /
                    ((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

        return {px, py};
    }

    vector<Point> getConvexHull(vector<Point>& points) {
        sort(points.begin(), points.end());
        vector<Point> hull;
        for(const auto& p : points) {
            while(hull.size() >= 2 && ccw(hull[hull.size()-2], hull.back(), p) <= 0)
                hull.pop_back();
            hull.push_back(p);
        }
        int s = hull.size();
        for(int i = points.size()-2; i >= 0; i--) {
            while(hull.size() >= s+1 && ccw(hull[hull.size()-2], hull.back(), points[i]) <= 0)
                hull.pop_back();
            hull.push_back(points[i]);
        }
        hull.pop_back();
        return hull;
    }

    long long getDist(const Point& p1, const Point& p2) {
        long long dx = p1.first - p2.first;
        long long dy = p1.second - p2.second;
        return dx*dx + dy*dy;
    }

    pair<int, int> rotatingCalipers(const vector<Point>& hull) {
        int n = hull.size();
        if(n <= 1) return {0, 0};
        if(n == 2) return {0, 1};

        int j = 1;
        long long maxDist = 0;
        pair<int, int> ret = {0, 0};

        for(int i = 0; i < n; i++) {
            int ni = (i+1)%n;
            Point vi = {hull[ni].first - hull[i].first, hull[ni].second - hull[i].second};

            while(true) {
                int nj = (j+1)%n;
                Point vj = {hull[nj].first - hull[j].first, hull[nj].second - hull[j].second};
                long long cross_prod = vi.first * vj.second - vi.second * vj.first;
                if(cross_prod <= 0) break;
                j = nj;
            }

            long long dist = getDist(hull[i], hull[j]);
            if(dist > maxDist) {
                maxDist = dist;
                ret = {i, j};
            }
        }

        return ret;
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int t;
        cin >> t;

        while(t--) {
            int x1, y1, x2, y2, x3, y3, x4, y4;
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

            pair<Point, Point> l1 = {make_pair(x1, y1), make_pair(x2, y2)};
            pair<Point, Point> l2 = {make_pair(x3, y3), make_pair(x4, y4)};

            if(isIntersect(l1, l2)) {
                cout << "YES\n";

                if(ccw(l1.first, l1.second, l2.first) * ccw(l1.first, l1.second, l2.second) != 0 ||
                   ccw(l2.first, l2.second, l1.first) * ccw(l2.first, l2.second, l1.second) != 0) {
                    auto [x, y] = intersection(l1, l2);
                    cout << fixed << setprecision(10) << x << " " << y << "\n";
                }
            } else {
                cout << "NO\n";
            }
        }
    }
}

// =======================
// Depth-First Search (DFS)
// =======================
namespace DFS {
    const int MAX = 1001;
    vector<int> graph[MAX];
    bool visited[MAX];
    int n, m;

    void dfs(int cur) {
        visited[cur] = true;
        cout << cur << ' ';

        for(int next : graph[cur]) {
            if(!visited[next]) {
                dfs(next);
            }
        }
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> n >> m;
        for(int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }

        for(int i = 1; i <= n; i++) {
            sort(graph[i].begin(), graph[i].end());
        }

        dfs(1);
        cout << "\n";
    }
}

// =======================
// Dijkstra's Algorithm
// =======================
namespace Dijkstra {
    #define INF 1e9
    typedef pair<int,int> pii;

    const int MAX = 20001;
    vector<pii> graph[MAX];
    int dist_arr[MAX];
    int V, E, start;

    void dijkstra() {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        fill(dist_arr, dist_arr + MAX, INF);

        dist_arr[start] = 0;
        pq.push({0, start});

        while(!pq.empty()) {
            int cur_dist = pq.top().first;
            int cur = pq.top().second;
            pq.pop();

            if(dist_arr[cur] < cur_dist) continue;

            for(auto &next : graph[cur]) {
                int next_vertex = next.first;
                int next_dist = cur_dist + next.second;

                if(next_dist < dist_arr[next_vertex]) {
                    dist_arr[next_vertex] = next_dist;
                    pq.push({next_dist, next_vertex});
                }
            }
        }
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> V >> E >> start;

        for(int i = 0; i < E; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
        }

        dijkstra();

        for(int i = 1; i <= V; i++) {
            if(dist_arr[i] == INF) cout << "INF\n";
            else cout << dist_arr[i] << '\n';
        }
    }
}

// =======================
// Fast Fourier Transform (FFT)
// =======================
namespace FFTNamespace {
    #define PI acos(-1)
    #define base complex<double>
    using namespace std;

    void fft(vector<base> &a, bool invert) {
        int n = a.size();

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            while (j >= bit) {
                j -= bit;
                bit >>= 1;
            }
            j += bit;
            if (i < j) swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double angle = 2 * PI / len * (invert ? -1 : 1);
            base wlen(cos(angle), sin(angle));
            for (int i = 0; i < n; i += len) {
                base w(1);
                for (int j = 0; j < len/2; j++) {
                    base u = a[i+j];
                    base v = a[i+j+len/2] * w;
                    a[i+j] = u + v;
                    a[i+j+len/2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (int i = 0; i < n; i++)
                a[i] /= n;
        }
    }

    vector<int> multiply(vector<int> &a, vector<int> &b) {
        vector<base> fa(a.begin(), a.end());
        vector<base> fb(b.begin(), b.end());

        int n = 1;
        while (n < a.size() + b.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);

        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];

        fft(fa, true);

        vector<int> result(n);
        for (int i = 0; i < n; i++)
            result[i] = round(fa[i].real());

        return result;
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, m;
        cout << "첫 번째 다항식의 차수를 입력하세요: ";
        cin >> n;

        cout << "첫 번째 다항식의 계수를 입력하세요 (차수 0부터): ";
        vector<int> a(n + 1);
        for (int i = 0; i <= n; i++)
            cin >> a[i];

        cout << "두 번째 다항식의 차수를 입력하세요: ";
        cin >> m;

        cout << "두 번째 다항식의 계수를 입력하세요 (차수 0부터): ";
        vector<int> b(m + 1);
        for (int i = 0; i <= m; i++)
            cin >> b[i];

        vector<int> result = multiply(a, b);

        cout << "곱셈 결과: ";
        for (int i = 0; i <= n + m; i++) {
            if (i > 0 && result[i] >= 0) cout << "+";
            if (result[i]) {
                cout << result[i];
                if (i > 0) cout << "x";
                if (i > 1) cout << "^" << i;
            }
        }
        cout << "\n";
    }
}

// =======================
// Floyd-Warshall Algorithm
// =======================
namespace FloydWarshall {
    const int MAX = 101;
    long long dist_arr[MAX][MAX];
    int n, m;

    void floydWarshall() {
        for(int k = 1; k <= n; k++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    if(dist_arr[i][k] != 1e18 && dist_arr[k][j] != 1e18) {
                        dist_arr[i][j] = min(dist_arr[i][j], dist_arr[i][k] + dist_arr[k][j]);
                    }
                }
            }
        }
    }

    void run() {
        ios_base::sync_with_stdio(0);
        cin.tie(0);

        cin >> n >> m;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(i == j) dist_arr[i][j] = 0;
                else dist_arr[i][j] = 1e18;
            }
        }

        for(int i = 0; i < m; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            dist_arr[a][b] = min(dist_arr[a][b], (long long)c);
        }

        floydWarshall();

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dist_arr[i][j] == 1e18) cout << "INF ";
                else cout << dist_arr[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}

// =======================
// Knuth-Morris-Pratt (KMP) Algorithm
// =======================
namespace KMP {
    vector<int> getFailure(string pattern) {
        int m = pattern.length();
        vector<int> fail(m, 0);

        int j = 0;
        for(int i = 1; i < m; i++) {
            while(j > 0 && pattern[i] != pattern[j]) {
                j = fail[j-1];
            }
            if(pattern[i] == pattern[j]) {
                fail[i] = ++j;
            }
        }
        return fail;
    }

    vector<int> kmpSearch(string text, string pattern) {
        vector<int> ans;
        vector<int> fail = getFailure(pattern);

        int n = text.length();
        int m = pattern.length();

        int j = 0;
        for(int i = 0; i < n; i++) {
            while(j > 0 && text[i] != pattern[j]) {
                j = fail[j-1];
            }
            if(text[i] == pattern[j]) {
                if(j == m-1) {
                    ans.push_back(i-m+1);
                    j = fail[j];
                }
                else {
                    j++;
                }
            }
        }
        return ans;
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        string text, pattern;
        getline(cin, text);
        getline(cin, pattern);

        vector<int> result = kmpSearch(text, pattern);

        cout << result.size() << '\n';
        for(int pos : result) {
            cout << pos + 1 << ' ';
        }
        cout << '\n';
    }
}

// =======================
// Knapsack Problems
// =======================
namespace Knapsack {
    // 0-1 Knapsack
    int knapsack01(vector<int>& weight, vector<int>& value, int maxWeight) {
        int n = weight.size();
        vector<int> dp(maxWeight + 1, 0);

        for(int i = 0; i < n; i++)
            for(int w = maxWeight; w >= weight[i]; w--)
                dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);

        return dp[maxWeight];
    }

    // Bounded Knapsack
    int boundedKnapsack(vector<int>& weight, vector<int>& value, vector<int>& count, int maxWeight) {
        int n = weight.size();
        vector<int> dp(maxWeight + 1, 0);

        for(int i = 0; i < n; i++)
            for(int k = 1; k <= count[i]; k++)
                for(int w = maxWeight; w >= weight[i]; w--)
                    dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);

        return dp[maxWeight];
    }

    // Unbounded Knapsack
    int unboundedKnapsack(vector<int>& weight, vector<int>& value, int maxWeight) {
        int n = weight.size();
        vector<int> dp(maxWeight + 1, 0);

        for(int w = 1; w <= maxWeight; w++)
            for(int i = 0; i < n; i++)
                if(weight[i] <= w)
                    dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);

        return dp[maxWeight];
    }

    // 0-1 Knapsack with Path Tracking
    vector<int> knapsackWithPath(vector<int>& weight, vector<int>& value, int maxWeight) {
        int n = weight.size();
        vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

        for(int i = 1; i <= n; i++) {
            for(int w = 0; w <= maxWeight; w++) {
                if(weight[i-1] <= w)
                    dp[i][w] = max(dp[i-1][w], dp[i-1][w - weight[i-1]] + value[i-1]);
                else
                    dp[i][w] = dp[i-1][w];
            }
        }

        vector<int> selected;
        int w = maxWeight;
        for(int i = n; i > 0; i--) {
            if(dp[i][w] != dp[i-1][w]) {
                selected.push_back(i-1);
                w -= weight[i-1];
            }
        }

        return selected;
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, maxWeight;
        cin >> n >> maxWeight;

        vector<int> weight(n), value(n), count(n, 1); // Assuming count=1 for 0-1 Knapsack
        for(int i = 0; i < n; i++)
            cin >> weight[i] >> value[i];
            // If bounded or unbounded, input 'count' as needed

        cout << "0-1 배낭문제: " << knapsack01(weight, value, maxWeight) << '\n';
        // For bounded knapsack, ensure 'count' is appropriately filled
        // cout << "Bounded 배낭문제: " << boundedKnapsack(weight, value, count, maxWeight) << '\n';
        cout << "Unbounded 배낭문제: " << unboundedKnapsack(weight, value, maxWeight) << '\n';

        cout << "선택된 물건들: ";
        vector<int> selected = knapsackWithPath(weight, value, maxWeight);
        for(int idx : selected)
            cout << idx << ' ';
        cout << '\n';
    }
}

// =======================
// Lazy Segment Tree (Range Updates and Queries)
// =======================
namespace LazySegmentTree {
    typedef long long ll;
    const int MAX = 100001;
    ll tree[4 * MAX], lazy_val[4 * MAX];
    int arr[MAX];
    int n;

    void build(int node, int start, int end) {
        lazy_val[node] = 0;
        if (start == end) {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;
        build(node*2, start, mid);
        build(node*2+1, mid+1, end);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    void update_range(int node, int start, int end, int left, int right, ll diff) {
        if(lazy_val[node] != 0) {
            tree[node] += (end - start + 1) * lazy_val[node];
            if(start != end) {
                lazy_val[node*2] += lazy_val[node];
                lazy_val[node*2+1] += lazy_val[node];
            }
            lazy_val[node] = 0;
        }

        if(start > right || end < left)
            return;

        if(start >= left && end <= right) {
            tree[node] += (end - start + 1) * diff;
            if(start != end) {
                lazy_val[node*2] += diff;
                lazy_val[node*2+1] += diff;
            }
            return;
        }

        int mid = (start + end) / 2;
        update_range(node*2, start, mid, left, right, diff);
        update_range(node*2+1, mid+1, end, left, right, diff);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    ll query_sum(int node, int start, int end, int left, int right) {
        if(start > right || end < left)
            return 0;

        if(lazy_val[node] != 0) {
            tree[node] += (end - start + 1) * lazy_val[node];
            if(start != end) {
                lazy_val[node*2] += lazy_val[node];
                lazy_val[node*2+1] += lazy_val[node];
            }
            lazy_val[node] = 0;
        }

        if(start >= left && end <= right)
            return tree[node];

        int mid = (start + end) / 2;
        return query_sum(node*2, start, mid, left, right) + 
               query_sum(node*2+1, mid+1, end, left, right);
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> n;
        for(int i = 0; i < n; i++) 
            cin >> arr[i];
        
        build(1, 0, n-1);

        int m;
        cin >> m;

        while(m--) {
            int op;
            cin >> op;

            if(op == 1) {
                int left, right;
                ll diff;
                cin >> left >> right >> diff;
                update_range(1, 0, n-1, left-1, right-1, diff);
            }
            else {
                int left, right;
                cin >> left >> right;
                cout << query_sum(1, 0, n-1, left-1, right-1) << '\n';
            }
        }
    }
}

// =======================
// Longest Increasing Subsequence (LIS)
// =======================
namespace LIS {
    // O(n log n) LIS
    vector<int> lis(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp;
        vector<int> idx(n);

        for(int i = 0; i < n; i++) {
            auto it = lower_bound(dp.begin(), dp.end(), arr[i]);
            if(it == dp.end()) {
                idx[i] = dp.size();
                dp.push_back(arr[i]);
            }
            else {
                idx[i] = it - dp.begin();
                *it = arr[i];
            }
        }

        int len = dp.size();
        vector<int> result;
        for(int i = n-1, j = len-1; i >= 0; i--) {
            if(idx[i] == j) {
                result.push_back(arr[i]);
                j--;
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }

    // O(n^2) LIS
    vector<int> lis_dp(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n, 1);
        vector<int> prev(n, -1);

        int maxLen = 1, endIdx = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(arr[j] < arr[i] && dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                    if(dp[i] > maxLen) {
                        maxLen = dp[i];
                        endIdx = i;
                    }
                }
            }
        }

        vector<int> result;
        for(int i = endIdx; i != -1; i = prev[i]) {
            result.push_back(arr[i]);
        }
        reverse(result.begin(), result.end());
        return result;
    }

    // Segment Tree based LIS (Advanced)
    class SegmentTree {
    private:
        vector<int> tree;
        int size;

        void updateTree(int node, int start, int end, int index, int value) {
            if(index < start || index > end) return;

            if(start == end) {
                tree[node] = max(tree[node], value);
                return;
            }

            int mid = (start + end) / 2;
            updateTree(node*2, start, mid, index, value);
            updateTree(node*2+1, mid+1, end, index, value);
            tree[node] = max(tree[node*2], tree[node*2+1]);
        }

        int queryTree(int node, int start, int end, int left, int right) {
            if(right < start || end < left) return 0;
            if(left <= start && end <= right) return tree[node];
            int mid = (start + end) / 2;
            return max(queryTree(node*2, start, mid, left, right),
                       queryTree(node*2+1, mid+1, end, left, right));
        }

    public:
        SegmentTree(int n) : size(n) {
            tree.resize(4*n, 0);
        }

        void update(int index, int value) {
            updateTree(1, 0, size-1, index, value);
        }

        int query(int left, int right) {
            return queryTree(1, 0, size-1, left, right);
        }
    };

    vector<int> lis_segtree(vector<int>& arr) {
        int n = arr.size();
        vector<pair<int,int>> pairs(n);
        for(int i = 0; i < n; i++) {
            pairs[i] = {arr[i], i};
        }
        sort(pairs.begin(), pairs.end());

        vector<int> compressed(n);
        for(int i = 0; i < n; i++) {
            compressed[pairs[i].second] = i;
        }

        SegmentTree seg(n);
        vector<int> dp(n, 0);
        int maxLen = 0, endIdx = 0;

        for(int i = 0; i < n; i++) {
            int val = seg.query(0, compressed[i]) + 1;
            dp[i] = val;
            seg.update(compressed[i], val);

            if(val > maxLen) {
                maxLen = val;
                endIdx = i;
            }
        }

        vector<int> result;
        int curLen = maxLen;
        int curNum = arr[endIdx];
        for(int i = endIdx; i >= 0; i--) {
            if(dp[i] == curLen && arr[i] <= curNum) {
                result.push_back(arr[i]);
                curLen--;
                curNum = arr[i];
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n;
        cin >> n;
        vector<int> arr(n);
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        vector<int> result1 = lis(arr);
        vector<int> result2 = lis_dp(arr);
        vector<int> result3 = lis_segtree(arr);

        cout << "LIS O(n log n) 길이: " << result1.size() << '\n';
        for(int x : result1) cout << x << ' ';
        cout << '\n';

        cout << "LIS O(n^2) 길이: " << result2.size() << '\n';
        for(int x : result2) cout << x << ' ';
        cout << '\n';

        cout << "LIS Segment Tree 길이: " << result3.size() << '\n';
        for(int x : result3) cout << x << ' ';
        cout << '\n';
    }
}

// =======================
// Maximum Flow (Dinic's Algorithm)
// =======================
namespace MaxFlow {
    const int MAX = 505;
    const int INF = 1e9;

    struct Edge {
        int to, cap, flow, rev;
        Edge(int to, int cap, int rev) : to(to), cap(cap), flow(0), rev(rev) {}
    };

    vector<Edge> graph[MAX];
    int level_arr[MAX], work_arr[MAX];
    int n, source, sink;

    void addEdge(int from, int to, int cap) {
        graph[from].emplace_back(to, cap, graph[to].size());
        graph[to].emplace_back(from, 0, graph[from].size()-1);
    }

    bool bfs() {
        memset(level_arr, -1, sizeof(level_arr));
        queue<int> q;
        q.push(source);
        level_arr[source] = 0;

        while(!q.empty()) {
            int cur = q.front();
            q.pop();

            for(auto &e : graph[cur]) {
                if(level_arr[e.to] == -1 && e.cap - e.flow > 0) {
                    level_arr[e.to] = level_arr[cur] + 1;
                    q.push(e.to);
                }
            }
        }
        return level_arr[sink] != -1;
    }

    int dfs(int cur, int flow) {
        if(cur == sink) return flow;

        for(int &i = work_arr[cur]; i < graph[cur].size(); i++) {
            Edge &e = graph[cur][i];
            if(level_arr[e.to] == level_arr[cur] + 1 && e.cap - e.flow > 0) {
                int df = dfs(e.to, min(flow, e.cap - e.flow));
                if(df > 0) {
                    e.flow += df;
                    graph[e.to][e.rev].flow -= df;
                    return df;
                }
            }
        }
        return 0;
    }

    int maxFlowFunction() {
        int flow = 0;
        while(bfs()) {
            memset(work_arr, 0, sizeof(work_arr));
            while(int df = dfs(source, INF)) {
                flow += df;
            }
        }
        return flow;
    }

    void run() {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);

        cin >> n;
        source = 0;
        sink = n-1;

        int m;
        cin >> m;

        for(int i = 0; i < m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            addEdge(u, v, c);
        }

        cout << maxFlowFunction() << '\n';
    }
}

// =======================
// Suffix Tree
// =======================
namespace SuffixTreeNamespace {
    struct Node {
        int start, end;
        map<char, int> next;
        Node(int s = -1, int e = -1) : start(s), end(e) {}
    };

    class SuffixTree {
    private:
        string s;
        vector<Node> tree;
        int remaining, activeNode, activeEdge, activeLength;
        int lastNewNode;

        int newNode(int start, int end = -1) {
            tree.emplace_back(start, end);
            return tree.size() - 1;
        }

        char activeEdgeChar() {
            return s[activeEdge];
        }

        bool walkDown(int node) {
            if(activeLength >= tree[node].end - tree[node].start + 1) {
                activeEdge += tree[node].end - tree[node].start + 1;
                activeLength -= tree[node].end - tree[node].start + 1;
                activeNode = node;
                return true;
            }
            return false;
        }

        void extend(int pos_in_s) {
            tree[0].end = pos_in_s;
            remaining++;
            lastNewNode = -1;

            while(remaining > 0) {
                if(activeLength == 0)
                    activeEdge = pos_in_s;

                if(tree[activeNode].next.find(s[activeEdge]) == tree[activeNode].next.end()) {
                    tree[activeNode].next[s[activeEdge]] = newNode(pos_in_s);
                    if(lastNewNode != -1) {
                        // Implement suffix link if needed
                        lastNewNode = -1;
                    }
                }
                else {
                    int next = tree[activeNode].next[s[activeEdge]];
                    if(walkDown(next))
                        continue;

                    if(s[tree[next].start + activeLength] == s[pos_in_s]) {
                        activeLength++;
                        if(lastNewNode != -1) {
                            // Implement suffix link if needed
                            lastNewNode = -1;
                        }
                        break;
                    }

                    int split = newNode(tree[next].start, tree[next].start + activeLength - 1);
                    tree[activeNode].next[s[activeEdge]] = split;
                    tree[split].next[s[pos_in_s]] = newNode(pos_in_s);
                    tree[next].start += activeLength;
                    tree[split].next[s[tree[next].start]] = next;

                    if(lastNewNode != -1)
                        lastNewNode = split;
                    else
                        lastNewNode = split;
                }

                remaining--;

                if(activeNode == 0 && activeLength > 0) {
                    activeLength--;
                    activeEdge = pos_in_s - remaining + 1;
                }
                else if(activeNode != 0) {
                    // Move suffix link if implemented
                    activeNode = 0; // For simplicity
                }
            }
        }

    public:
        SuffixTree(string str) : s(str + "$"), remaining(0), activeNode(0), activeEdge(0), activeLength(0), lastNewNode(-1) {
            tree.reserve(2 * s.length());
            tree.emplace_back(); // Root node
            for(int i = 0; i < s.length(); i++)
                extend(i);
        }

        void print(int node = 0, int depth = 0) {
            for(auto &[ch, next] : tree[node].next) {
                for(int i = 0; i < depth; i++) cout << "  ";
                for(int i = tree[next].start; i <= (tree[next].end == -1 ? (int)s.length()-1 : tree[next].end); i++) {
                    cout << s[i];
                }
                cout << '\n';
                print(next, depth + 1);
            }
        }

        bool findPattern(string pattern) {
            int node = 0;
            int pos = 0;
            while(pos < pattern.length()) {
                char ch = pattern[pos];
                if(tree[node].next.find(ch) == tree[node].next.end())
                    return false;
                node = tree[node].next[ch];
                int edgeLen = (tree[node].end == -1 ? (int)s.length()-1 : tree[node].end) - tree[node].start + 1;
                for(int i = 0; i < edgeLen && pos < pattern.length(); i++, pos++) {
                    if(s[tree[node].start + i] != pattern[pos])
                        return false;
                }
            }
            return true;
        }
    };

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        string s;
        cin >> s;

        SuffixTree st(s);
        cout << "Suffix Tree Structure:\n";
        st.print();

        int q;
        cin >> q;
        while(q--) {
            string pattern;
            cin >> pattern;
            if(st.findPattern(pattern)) {
                cout << "Found\n";
            } else {
                cout << "Not Found\n";
            }
        }
    }
}

// =======================
// Sweeping Algorithms
// =======================
namespace Sweeping {
    // Example: Finding maximum number of overlapping intervals
    typedef pair<int, int> pii;

    int maxOverlap(vector<pii>& points) {
        vector<pair<int, int>> events;
        for(auto &[start, end] : points) {
            events.emplace_back(start, 1);    // 1 for start
            events.emplace_back(end, -1);     // -1 for end
        }
        sort(events.begin(), events.end());

        int ret = 0, cnt = 0;
        for(auto &[x, type] : events) {
            cnt += type;
            ret = max(ret, cnt);
        }
        return ret;
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n;
        cin >> n;
        vector<pii> points(n);
        for(int i = 0; i < n; i++) {
            cin >> points[i].first >> points[i].second;
        }

        cout << "최대 겹치는 간격의 개수: " << maxOverlap(points) << '\n';
    }
}

// =======================
// Topological Sort
// =======================
namespace TopologicalSort {
    class Graph {
        int V;
        vector<vector<int>> adj;
        vector<int> inDegree;

    public:
        Graph(int vertices) {
            V = vertices;
            adj.resize(V);
            inDegree.resize(V, 0);
        }

        void addEdge(int v1, int v2) {
            adj[v1].push_back(v2);
            inDegree[v2]++;
        }

        void topologicalSortFunction() {
            queue<int> q;
            vector<int> result;

            for(int i = 0; i < V; i++) {
                if(inDegree[i] == 0) {
                    q.push(i);
                }
            }

            while(!q.empty()) {
                int curr = q.front();
                q.pop();
                result.push_back(curr);

                for(int next : adj[curr]) {
                    inDegree[next]--;
                    if(inDegree[next] == 0) {
                        q.push(next);
                    }
                }
            }

            if(result.size() != V) {
                cout << "사이클이 존재합니다.\n";
                return;
            }

            for(int v : result) {
                cout << v + 1 << " ";
            }
            cout << "\n";
        }
    };

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int N, M;
        cout << "정점의 수와 간선의 수를 입력하세요: ";
        cin >> N >> M;

        Graph g(N);

        cout << "간선 정보를 입력하세요 (각 줄에 출발 정점과 도착 정점): \n";
        for(int i = 0; i < M; i++) {
            int v1, v2;
            cin >> v1 >> v2;
            g.addEdge(v1-1, v2-1);
        }

        cout << "위상 정렬 결과: ";
        g.topologicalSortFunction();
    }
}

// =======================
// Trie Data Structure
// =======================
namespace TrieNamespace {
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;

        TrieNode() : isEnd(false) {
            for(int i = 0; i < 26; i++) children[i] = nullptr;
        }

        ~TrieNode() {
            for(int i = 0; i < 26; i++)
                if(children[i])
                    delete children[i];
        }

        void insert(string& str, int idx) {
            if(idx == str.length()) {
                isEnd = true;
                return;
            }

            int cur = str[idx] - 'a';
            if(children[cur] == nullptr)
                children[cur] = new TrieNode();
            children[cur]->insert(str, idx + 1);
        }

        bool find(string& str, int idx) {
            if(idx == str.length())
                return isEnd;

            int cur = str[idx] - 'a';
            if(children[cur] == nullptr)
                return false;
            return children[cur]->find(str, idx + 1);
        }
    };

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n, m;
        cin >> n;

        TrieNode* root = new TrieNode();

        for(int i = 0; i < n; i++) {
            string s;
            cin >> s;
            root->insert(s, 0);
        }

        cin >> m;
        for(int i = 0; i < m; i++) {
            string s;
            cin >> s;
            cout << (root->find(s, 0) ? "1\n" : "0\n");
        }

        delete root;
    }
}

// =======================
// Two Pointers Technique
// =======================
namespace TwoPointers {
    // 1. Counting subarrays with sum S
    int twoPointer1(vector<int>& arr, long long S) {
        int n = arr.size();
        int start = 0, end = 0;
        long long sum = 0;
        int cnt = 0;

        while(start < n) {
            while(end < n && sum < S) {
                sum += arr[end++];
            }
            if(sum == S) cnt++;
            sum -= arr[start++];
        }
        return cnt;
    }

    // 2. Counting pairs with sum X (sorted array)
    int twoPointer2(vector<int>& arr, int X) {
        int n = arr.size();
        int left = 0, right = n-1;
        int cnt = 0;

        while(left < right) {
            int sum = arr[left] + arr[right];
            if(sum == X) {
                cnt++;
                left++;
                right--;
            }
            else if(sum < X) {
                left++;
            }
            else {
                right--;
            }
        }
        return cnt;
    }

    // 3. Minimum sum of subarray with length M
    int twoPointer3(vector<int>& arr, int M) {
        int n = arr.size();
        int sum = 0;
        int minSum;

        for(int i = 0; i < M; i++)
            sum += arr[i];
        minSum = sum;

        for(int i = M; i < n; i++) {
            sum += arr[i] - arr[i-M];
            minSum = min(minSum, sum);
        }
        return minSum;
    }

    // 4. Longest subarray with at most K distinct elements
    int twoPointer4(vector<int>& arr, int K) {
        int n = arr.size();
        int start = 0, end = 0;
        map<int, int> cnt;
        int maxLen = 0;

        while(end < n) {
            cnt[arr[end]]++;
            while(cnt.size() > K) {
                if(--cnt[arr[start]] == 0)
                    cnt.erase(arr[start]);
                start++;
            }
            maxLen = max(maxLen, end - start + 1);
            end++;
        }
        return maxLen;
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        // Example usage of two pointers
        // 1. Counting subarrays with sum S
        int n1;
        long long S;
        cin >> n1 >> S;
        vector<int> arr1(n1);
        for(auto &x : arr1) cin >> x;
        cout << "연속된 부분합이 " << S << "인 경우의 수: " << twoPointer1(arr1, S) << '\n';

        // 2. Counting pairs with sum X
        int n2, X;
        cin >> n2 >> X;
        vector<int> arr2(n2);
        for(auto &x : arr2) cin >> x;
        sort(arr2.begin(), arr2.end());
        cout << "두 수의 합이 " << X << "인 쌍의 개수: " << twoPointer2(arr2, X) << '\n';

        // 3. Minimum sum of subarray with length M
        int M;
        cin >> M;
        cout << "길이가 " << M << "인 최소합 구간의 합: " << twoPointer3(arr2, M) << '\n';

        // 4. Longest subarray with at most K distinct elements
        int K;
        cin >> K;
        cout << "서로 다른 값이 " << K << "개 이하인 가장 긴 연속 부분 수열의 길이: " << twoPointer4(arr2, K) << '\n';
    }
}

// =======================
// Union-Find (Disjoint Set Union)
// =======================
namespace UnionFindNamespace {
    class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;
        vector<int> size;

    public:
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            size.resize(n, 1);
            for(int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int findSet(int x) {
            if(parent[x] == x) return x;
            return parent[x] = findSet(parent[x]);
        }

        void unite(int x, int y) {
            x = findSet(x);
            y = findSet(y);

            if(x == y) return;

            if(rank[x] < rank[y]) swap(x, y);
            parent[y] = x;
            size[x] += size[y];

            if(rank[x] == rank[y]) rank[x]++;
        }

        bool sameSet(int x, int y) {
            return findSet(x) == findSet(y);
        }

        int getSize(int x) {
            return size[findSet(x)];
        }
    };

    struct Edge {
        int u, v, w;
        Edge(int u, int v, int w) : u(u), v(v), w(w) {}
        bool operator<(const Edge& o) const { return w < o.w; }
    };

    long long kruskal(int V, vector<Edge>& edges) {
        sort(edges.begin(), edges.end());
        UnionFind uf(V);
        long long ret = 0;

        for(auto &e : edges) {
            if(!uf.sameSet(e.u, e.v)) {
                uf.unite(e.u, e.v);
                ret += e.w;
            }
        }
        return ret;
    }

    long long prim(int V, vector<vector<pair<int,int>>>& adj) {
        vector<bool> vis(V, false);
        vector<int> minW(V, INT_MAX);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

        long long ret = 0;
        minW[0] = 0;
        pq.push({0, 0});

        while(!pq.empty()) {
            auto [w, u] = pq.top(); pq.pop();
            if(vis[u]) continue;

            vis[u] = true;
            ret += w;

            for(auto &[v, nw] : adj[u]) {
                if(!vis[v] && nw < minW[v]) {
                    minW[v] = nw;
                    pq.push({nw, v});
                }
            }
        }
        return ret;
    }

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int V, E; 
        cin >> V >> E;
        vector<Edge> edges;
        vector<vector<pair<int,int>>> adj(V, vector<pair<int,int>>());

        for(int i = 0; i < E; i++) {
            int u, v, w; 
            cin >> u >> v >> w;
            u--; v--;
            edges.emplace_back(u, v, w);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        cout << kruskal(V, edges) << '\n';
        cout << prim(V, adj) << '\n';
    }
}

// =======================
// Merge Sort Tree
// =======================
namespace MergeSortTreeNamespace {
    class MergeSortTree {
    private:
        int n;
        vector<vector<int>> tree;
        string s; // For example purposes

        void build(int node, int start, int end, const vector<int>& arr) {
            if(start == end) {
                tree[node] = {arr[start]};
                return;
            }

            int mid = (start + end) >> 1;
            build(node*2, start, mid, arr);
            build(node*2+1, mid+1, end, arr);

            tree[node].resize(tree[node*2].size() + tree[node*2+1].size());
            merge(tree[node*2].begin(), tree[node*2].end(),
                  tree[node*2+1].begin(), tree[node*2+1].end(),
                  tree[node].begin());
        }

        int query(int node, int start, int end, int left, int right, int k) {
            if(right < start || end < left) return 0;
            if(left <= start && end <= right) {
                return tree[node].end() - upper_bound(tree[node].begin(), tree[node].end(), k);
            }

            int mid = (start + end) >> 1;
            return query(node*2, start, mid, left, right, k) + 
                   query(node*2+1, mid+1, end, left, right, k);
        }

    public:
        MergeSortTree(const vector<int>& arr) {
            n = arr.size();
            tree.resize(4*n);
            build(1, 0, n-1, arr);
        }

        int query(int left, int right, int k) {
            return query(1, 0, n-1, left, right, k);
        }
    };

    void run() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        int n;
        cin >> n;

        vector<int> arr(n);
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        MergeSortTree mst(arr);

        int q;
        cin >> q;
        while(q--) {
            int l, r, k;
            cin >> l >> r >> k;
            l--; r--;
            cout << mst.query(l, r, k) << '\n';
        }
    }
}

// =======================
// Minimum Cost Maximum Flow (MCMF) - Commented Out
// =======================
namespace MCMF {
    // 구현이 복잡하여 예시에서는 제외합니다.
    // 필요시 별도로 구현하거나 참고 자료를 활용하시기 바랍니다.
}

// =======================
// Longest Increasing Subsequence (LIS)
// =======================

namespace LISNamespace {
    // Already included in LIS namespace above
}

// =======================
// Additional Algorithms
// =======================
// 동일한 방식으로 나머지 알고리즘을 네임스페이스로 추가할 수 있습니다.
// 예를 들어, SuffixTree, SegmentTreeBeats 등.

    // 예시: Union-Find (Disjoint Set Union)
    // 이미 UnionFindNamespace에 포함되어 있음
    // SuffixTree 등도 별도의 네임스페이스로 추가

// =======================
// Main Function with Menu
// =======================
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int choice;
    while(true){
        cout << "==============================\n";
        cout << " Competitive Programming Template\n";
        cout << "==============================\n";
        cout << "Select algorithm to run:\n";
        cout << "1. TwoSAT\n";
        cout << "2. Bellman-Ford\n";
        cout << "3. BFS\n";
        cout << "4. Binary Search\n";
        cout << "5. Bipartite Matching\n";
        cout << "6. Bitmask Operations\n";
        cout << "7. Boyer-Moore String Search\n";
        cout << "8. Computational Geometry (Convex Hull & Rotating Calipers)\n";
        cout << "9. DFS\n";
        cout << "10. Dijkstra's Algorithm\n";
        cout << "11. Fast Fourier Transform (FFT)\n";
        cout << "12. Floyd-Warshall Algorithm\n";
        cout << "13. KMP String Search\n";
        cout << "14. Knapsack Problems\n";
        cout << "15. Lazy Segment Tree\n";
        cout << "16. Longest Increasing Subsequence (LIS)\n";
        cout << "17. Maximum Flow (Dinic's Algorithm)\n";
        cout << "18. Merge Sort Tree\n";
        // Add more algorithms as needed
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                TwoSAT::run();
                break;
            case 2:
                BellmanFord::run();
                break;
            case 3:
                BFS::run();
                break;
            case 4:
                BinarySearch::run();
                break;
            case 5:
                BipartiteMatching::run();
                break;
            case 6:
                Bitmask::run();
                break;
            case 7:
                BoyerMoore::run();
                break;
            case 8:
                ComputationalGeometry::run();
                break;
            case 9:
                DFS::run();
                break;
            case 10:
                Dijkstra::run();
                break;
            case 11:
                FFTNamespace::run();
                break;
            case 12:
                FloydWarshall::run();
                break;
            case 13:
                KMP::run();
                break;
            case 14:
                Knapsack::run();
                break;
            case 15:
                LazySegmentTree::run();
                break;
            case 16:
                LIS::run();
                break;
            case 17:
                MaxFlow::run();
                break;
            case 18:
                MergeSortTreeNamespace::run();
                break;
            // Add more cases for additional algorithms
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
        cout << "\n";
    }
}