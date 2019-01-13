#include <iostream>
#include <vector>

int threemin(int x, int y, int z)
{
    int v = std::min(x, y);
    return std::min(v, z);
}

int get_change(int m)
{
    std::vector<int> dp(m + 1, 0);

    for (int i = 0; i <= m; ++i)
    {
        switch (i)
        {
        case 0:
            dp.at(i) = 0;
            break;
        case 1:
            dp.at(i) = 1;
            break;
        case 2:
            dp.at(i) = 2;
            break;
        case 3:
            dp.at(i) = 1;
            break;
        case 4:
            dp.at(i) = 1;
            break;
        default:
            int minv = threemin(dp[i - 1], dp[i - 3], dp[i - 4]);
            // std::cout << "!" << i << "?" << minv << "?";
            dp.at(i) = minv + 1;
        }
        // std::cout << i << " " << dp[i] << "\n";
    }
    return dp[m];
}

int main()
{
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
