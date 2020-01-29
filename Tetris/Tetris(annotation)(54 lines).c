#include<windows.h>
#include<conio.h>
int T, X ,Y, c, i, j, k, map[250] = { 0 }, node[28][4] = {
//形状，根坐标，输入&循环变量，ijk循环变量，map地图，node节点，下面为7种形状*4种方向*4个节点包含宽*Y+X的数据
	-1,0,1,-11,10,0,-10,-9,11,-1,0,1,9,10,0,-10, -1,0,1,-9,10,11,0,-10,9,-1,0,1,
	10,0,-10,-11, 9,10,0,1,11,0,1,-10,9,10,0,1,11,0,1,-10, 10,11,-1,0,10,0,1,-9,
	10,11,-1,0,10,0,1,-9,-1,0,1,-10,10,0,1,-10,10,-1,0,1,10,-1,0,-10,20,10,0,-10,
	-1,0,1,2,20,10,0,-10,-1,0,1,2,10,11,0,1,10,11,0,1,10,11,0,1,10,11,0,1 };
//移动
int move(int* v, int l) {
	for (*v += l, i = 0; i < 4 && (j = (node[T][i] + 11) % 10 - 1 + X, 1); i++)
//先移动，遍历4个节点，j=节点X坐标
		if ((j < 0 || 9 < j || 24 < (node[T][i] + 11) / 10 - 1 + Y ||
//越界判断
			map[node[T][i] + Y * 10 + X]) && (*v -= l, 1))return 0;
//判断当前节点是否有方块，如果前面有为真，则回到移动之前的位置，并且返回0
	return 1;
}
//下落
void down() {
	if (move(&Y, 1) || Y < 2 && (exit(!_getch()), 0))return;
//向下移动，如果为真直接返回，为假则再判定当前Y坐标，如果<2则退出并阻塞
	for (i = 0; i < 4 && (map[node[T][i] + Y * 10 + X] = 1); i++);
//4个节点在地图对应的位置赋值
	for (i = 250, k = 0; i >= 10 || (c = 0); i % 10 == 0 && (k = 0))
//i从最后一行的行尾向前遍历，直到第一行的行尾，每遇到行头则k复位，结束时c=0
		if (--i, (k += map[i]) == 10)
//k累计当前行数的方块，如果为10，则执行消行，消行原理，上面的数据覆盖下面的数据
			for (j = i + 9; j > 9 || (i += 10, 0); map[j] = map[j - 10], j--);
//j从当前行尾开始，当前的数据等于上面的数据，直到第一行行尾结束，结束时i回到行尾
}
//主函数
int main() {
	srand((unsigned)malloc(!system("mode con: cols=20 lines=25")));
//初始化随机种子，并设置窗口大小
	for (; c || (X = 4, Y = 1, T = rand() % 7 * 4, c = 1); down(), Sleep(150)) {
//开始循环；c=0时重置根坐标和形状及本身；固定的下落和延时
		if (_kbhit() && (c = _getch())) {
//检测是否有输入，有则获取并判断
			if (c == 'w' || c == 'W')move(&T, (T % 4) < 3 ? 1 : -3);
//w旋转
			else if (c == 'd' || c == 'D')X < 9 && move(&X, 1);
//d右移
			else if (c == 'a' || c == 'A')X > 0 && move(&X, -1);
//a左移
			else if (c == 's' || c == 'S')down();
//s下落
		}
		for (i = system("cls"); i < 4 && (map[node[T][i] + Y * 10 + X] = -1); i++);
//清屏，节点赋值为-1
		for (i = 0; i < 250; i++)_cputs(map[i] ? "[]" : "  "), map[i] += map[i] < 0;
//打印，并复位节点
	}
}
