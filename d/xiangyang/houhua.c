// Room: houhua.c

inherit ROOM;

void create()
{
	set("short", "后花园");
	set("long", @LONG
你缓步向后山走去。那山也不甚高，身周树木葱翠，四下里轻烟薄雾，出没于枝
叶之间。你足踏软草，竟连脚步也是悄无声息。将到山顶，转了两个弯，一阵清风，
四周全是花香。放眼望去，漫坡尽是红色、白色、黄色的玫瑰。
LONG
	);
 

	set("objects", ([
		__DIR__"npc/wenyi": 1,
	]));
	
	set("exits", ([
		"north": __DIR__"tianjing",
	]) );

	setup();
}
