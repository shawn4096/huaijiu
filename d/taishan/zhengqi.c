// Room: /d/taishan/zhengqi.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "正气厅");
	set("long", @LONG
这里是封禅台右边的正气厅，厅内两边各侍立着几位红衣武士，
看上去杀气腾腾，令人凛然而生惧意。
LONG
	);

	set("exits", ([
		"east" : __DIR__"fengchan",
	]));

	set("objects",([
		__DIR__"npc/wei-shi2" : 3,
	]));

        set("no_clean_up", 1);

	setup();
}
