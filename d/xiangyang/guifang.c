// Room: guifang.c

inherit ROOM;

void create()
{
	set("short", "闺房");
	set("long", @LONG
你上得楼来，眼前一耀，先闻到一阵幽幽的香气，只见房中点了一支大红烛，照
得满室生春，床上珠罗纱的帐子，白色缎被上绣着一只黄色的凤凰，壁上挂着一幅工
笔仕女图。床前桌上放着一张雕花端砚，几件碧玉玩物。笔筒中插了大大小小六七支
笔，西首一张几上供着一盆兰花，架上停着一只白鹦鹉。满室锦绣，连椅披上也绣了
花。
LONG
	);
 

	set("objects", ([
//		__DIR__"npc/wenqq": 1,
	]));
	
	set("exits", ([
		"west":__DIR__"tianjing",
	]) );

	setup();
}
