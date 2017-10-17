int N, NP, NC, M;
struct Edge
{
    int u, v, cap;
    Edge() {}
    Edge(int u, int v, int cap): u(u), v(v), cap(cap) {}
} es[150 * 150];
int R, S, T;
vector<int> tab[109]; // �߼�
int dis[109];
int current[109];
void addedge(int u, int v, int cap)
{
    tab[u].push_back(R);
    es[R++] = Edge(u, v, cap); // �����
    tab[v].push_back(R);
    es[R++] = Edge(v, u, 0); // ���������Ϊ0
    // ������±�ͨ�����͵õ�������±�, 2 ^ 1 == 3 ; 3 ^ 1 == 2
}
int BFS()
{
    queue<int> q;
    q.push(S);
    memset(dis, 0x3f, sizeof(dis));
    dis[S] = 0;
    while (!q.empty())
    {
        int h = q.front();
        q.pop();
        for (int i = 0; i < tab[h].size(); i++)
        {
            Edge &e = es[tab[h][i]];
            if (e.cap > 0 && dis[e.v] == 0x3f3f3f3f)
            {
                dis[e.v] = dis[h] + 1;
                q.push(e.v);
            }
        }
    }
    return dis[T] < 0x3f3f3f3f; // �����Ƿ��ܹ�������
}
int dinic(int x, int maxflow)
{
    if (x == T)
        return maxflow;
    // i = current[x] ��ǰ���Ż�
    for (int i = current[x]; i < tab[x].size(); i++)
    {
        current[x] = i;
        Edge &e = es[tab[x][i]];
        if (dis[e.v] == dis[x] + 1 && e.cap > 0)
        {
            int flow = dinic(e.v, min(maxflow, e.cap));
            if (flow)
            {
                e.cap -= flow; // �������������
                es[tab[x][i] ^ 1].cap += flow; // �������������
                return flow;
            }
        }
    }
    return 0; // �Ҳ�������· �˳�
}
int DINIC()
{
    int ans = 0;
 
    while (BFS()) // �����ֲ�ͼ
    {
        int flow;
        memset(current, 0, sizeof(current)); // BFS��Ӧ����յ�ǰ������
        while (flow = dinic(S, 0x3f3f3f3f)) // һ��BFS���Խ��ж������
            ans += flow;
    }
    return ans;
}
