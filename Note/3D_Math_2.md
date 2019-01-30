# 3D Math Primer for Graphics and Game Development

---

### 向量

```
# ====
左手坐标系：（左手）拇指x，食指y，中指z
右手坐标系：（右手）拇指x，食指y，中指z

# ====
向量投影的计算：V平行 与 V垂直

# ====
向量点乘：对应分量相乘，a.b = ||a||*||b||cosθ
[x1 y1 z1] . [x2 y2 z2] = [x1*x2 y1*y2 z1*z2]

向量叉乘：根据叉乘公式，axb = ||a||*||b||sinθ，值为a和b所组成平行四边形的面积
--  --     -------------
x1  x2     y1*z2 - y2*z1
y1  y2  =  z1*x2 - z2*x1 
z1  z2     x1*y2 - x2*y1
--  --     -------------
```

### 矩阵

```
# ====
矩阵：用于描述两个坐标系统之间的关系。通过定义一种运算将一个坐标系中的向量转换到另一个坐标系中

# ====
矩阵积的转置等于矩阵转置后反向相乘：(AB)^T = B^T.A^T

# ====
线性变换：保留直线和平行线，不移动原点。包括 旋转-缩放-投影-镜像-仿射

# ====
将3x3矩阵表示为基向量的线性组合：p-q-r为基向量，该坐标系中任意向量表示为 v = xp + yq + zr
（思考为何如此表示？提示：p = [1 0 0]，q = ...，v = [1 2 3] = 1*[1 0 0] + 2*[0 1 0] + 3*[0 0 1]）
    |p|   |px py pz|
M = |q| = |qx qy qz|
    |r|   |rx ry rz|
矩阵中的每一行都能解释为转换后（坐标系）的基向量
```

### 线性变换

```
# ====
2D旋转公式：
R(θ) = |cosθ  sinθ|
       |-sinθ cosθ|
（如何证明？提示：将 p = [1 0]，q = [0 1] 在坐标系中顺时针旋转θ度，让它们作为新坐标系基向量，
得到 p = [cosθ sinθ]，q = [-sinθ cosθ]）

# ====
3D旋转时，左手坐标系使用左手法则，拇指为转轴，朝向手握紧的方向为正向。
绕x轴旋转公式：
        |1    0     0|
Rx(θ) = |0  cosθ sinθ|
        |0 -sinθ cosθ|

绕y轴旋转公式：
        |cosθ 0 -sinθ|
Ry(θ) = |0    1     0|
        |sinθ 0  cosθ|

绕z轴旋转公式：
        | cosθ sinθ 0|
Rz(θ) = |-sinθ cosθ 0|
        |    0    0 1|

# ====
（
如何计算绕任意轴n的旋转公式？
提示：在垂直于n的平面中解决该问题，将v分解为平行于n的向量，和垂直于n的向量，通过n与v垂直叉乘获得w，
旋转时v平行不变，v垂直在v垂直与w组成平面中旋转，即v垂直在2D平面中旋转。

转换后的v = [v - (v.n)n]cosθ + (nxv)sinθ + (v.n)n
注意：若(v.n) = a，则(v.n)n = [a.nx  a.ny  a.nz]

p = [1 0 0]，转换后的p =
[nx.nx(1-cosθ)+cosθ    nx.ny(1-cosθ)+nzsinθ    nx.nz(1-cosθ)-nysinθ]

q = [0 1 0]，转换后的q =
[nx.ny(1-cosθ)-nzsinθ    ny.ny(1-cosθ)+cosθ    ny.nz(1-cosθ)+nxsinθ]

r = [0 0 1]，转换后的r =
[nx.nz(1-cosθ)+nysinθ    ny.nz(1-cosθ)-nxsinθ    nz.nz(1-cosθ)+cosθ]

绕任意轴n的旋转公式为：
          |  nx.nx(1-cosθ)+cosθ    nx.ny(1-cosθ)+nzsinθ    nx.nz(1-cosθ)-nysinθ|
R(n, θ) = |nx.ny(1-cosθ)-nzsinθ      ny.ny(1-cosθ)+cosθ    ny.nz(1-cosθ)+nxsinθ|
          |nx.nz(1-cosθ)+nysinθ    ny.nz(1-cosθ)-nxsinθ      nz.nz(1-cosθ)+cosθ|
）

# ====
沿轴的3D缩放公式：
                |kx   0   0|
S(kx, ky, kz) = | 0  ky   0|
                | 0   0  kz|
# ====
沿任意轴n进行缩放时：
将v沿n分解为v平行与v垂直，缩放后v平行放大k倍为 k(v.n)n，v垂直不变为 v - (v.n)n，
v为：k(v.n)n + v - (v.n)n = v + (k-1)(v.n)n
p = [1 0 0]，缩放后 p = [1+(k-1)nx.nx  (k-1)nx.ny   (k-1)nx.nz]
绕任意轴n的3D缩放公式为：
          |1+(k-1)nx.nx      (k-1)nx.ny      (k-1)nx.nz|
S(n, k) = |  (k-1)nx.ny    1+(k-1)ny.ny      (k-1)ny.nz|
          |  (k-1)nx.nz      (k-1)ny.nz    1+(k-1)nz.nz|

# ====
正交投影：将某个方向上用来零作为缩放因子，所有点被拉平至垂直的轴（2D）或平面（3D）上。
向xy平面投影的3D矩阵：
                      |1 0 0|
Pxy = S([0 0 1], 0) = |0 1 0|
                      |0 0 0|

向任意平面投影：设n为垂直于该平面的向量，则在该方向上缩放为0即可
向任意平面投影的3D矩阵：
                 |1+(0-1)nx.nx      (0-1)nx.ny      (0-1)nx.nz|         |1-nx.nx     -nx.ny     -nx.nz|
P(n) = S(n, 0) = |  (0-1)nx.ny    1+(0-1)ny.ny      (0-1)ny.nz|    =    | -nx.ny    1-ny.ny     -ny.nz|
                 |  (0-1)nx.nz      (0-1)ny.nz    1+(0-1)nz.nz|         | -nx.nz     -ny.nz    1-nz.nz|

# ====
镜像：将物体沿直线（2D）或平面（3D）翻转

沿任意平面镜像的3D矩阵：
                  |1+(-1-1)nx.nx      (-1-1)nx.ny      (-1-1)nx.nz|         |1-2nx.nx     -2nx.ny     -2nx.nz|
P(n) = S(n, -1) = |  (-1-1)nx.ny    1+(-1-1)ny.ny      (-1-1)ny.nz|    =    | -2nx.ny    1-2ny.ny     -2ny.nz|
                  |  (-1-1)nx.nz      (-1-1)ny.nz    1+(-1-1)nz.nz|         | -2nx.nz     -2ny.nz    1-2nz.nz|

# ====
切变：坐标系扭曲变换
3D切变矩阵：
           |1 0 0|                |1 0 0|                |1 s t|
Hxy(s,t) = |0 1 0|    Hxz(s, t) = |s 1 t|    Hyz(s, t) = |0 1 0|
           |s t 1|                |0 0 1|                |0 0 1|
Hxy(s,t)中，随着z从(0,z)变化，x跟着从(0,s)变化，y跟着从(0,t)变化

# ====

```
