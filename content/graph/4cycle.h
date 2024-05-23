/**
 * Author: Kaiyuan Liu
 * Date: 2024-05-22
 * Description: For finding 4-cycles.
 * Time: $O(E \sqrt{E})$
 */
#pragma once

for (int u = 1; u <= n; u++)
    for (int v : E[u])
        if (deg[u] > deg[v] || (deg[u] == deg[v] && u > v)) E1[u].push_back(v);
for (int a = 1; a <= n; a++) {
    for (int b : E1[a])
        for (int c : E[b]) {
            if (deg[a] < deg[c] || (deg[a] == deg[c] && a <= c)) continue;
            total += cnt[c]++;
        }
    for (int b : E1[a])
        for (int c : E[b]) cnt[c] = 0;
}
