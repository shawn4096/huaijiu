// 花轿里面

inherit ROOM;

int do_get(string);

void create()
{
	set("short", "花轿里");
	set("long", @LONG
这是花轿里面，空间狭小，只有一个座位，两边的窗户都用红布
蒙着，你看不见窗外景物，只能感觉到轿子正在被抬着，摇摇晃晃地
走着。
LONG
	);

	setup();
}
