// Room: /d/taishan/xiayi.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "侠义厅");
	set("long", @LONG
这里是封禅台左边的侠义厅，厅两边各侍立着几位红衣武士�
看上去威风凛凛，自有一股庄严气象。
LONG
	);

	set("exits", ([
		"west" : __DIR__"fengchan",
	]));

	set("objects",([
		__DIR__"npc/wei-shi2" : 3,
	]));

        set("no_clean_up", 1);

	setup();
}
