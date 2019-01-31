// Room: /d/taishan/xiayi.c
// Date: pishou 97/6

inherit ROOM;

void create()
{
	set("short", "ÏÀÒåÌü");
	set("long", @LONG
ÕâÀïÊÇ·âìøÌ¨×ó±ßµÄÏÀÒåÌü£¬ÌüÁ½±ß¸÷ÊÌÁ¢×Å¼¸Î»ºìÒÂÎäÊ¿£
¿´ÉÏÈ¥Íş·çÁİÁİ£¬×ÔÓĞÒ»¹É×¯ÑÏÆøÏó¡£
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
