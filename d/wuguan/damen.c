// Room: damen.c

inherit ROOM;

void create()
{
	set("short", "武馆大门");
	set("long", @LONG
你走到一座高宅大院的门口，大门紧闭，门口站着几个家丁，一个个腆胸叠肚，
一副要找人麻烦的样子。门前左右有两个石狮子，四五级青石台阶上是两扇钉满铜
钉的大门。看得出这里是当地大豪的住所。
LONG);
	set("objects", ([
		"/d/xiangyang/npc/jiading":2,
	]));
	
	set("exits", ([
		"south": "/d/xiangyang/shide",
		"north": "/d/xiangyang/xiaoxiang1",
	]) );
	set("outdoors","武馆");
	setup();
}
