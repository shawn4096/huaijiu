// andao1.c
// Created by Numa 19991021

#include <ansi.h>
inherit ROOM;
#include "andao.h"

void create()
{
	set("short", "暗道");
	set("long", @LONG
这是一条通往监狱的暗道，两旁有许多各式的刑具，在微弱的烛光
之下，散发着冰冷的寒光，令人越看越是心中发毛，想像受刑之人
那种惨状及那凄惨的叫声，心中更感到一阵惊怖。
LONG
	);
	set("exits", ([ 
		"west":	__DIR__"houdian",
		"north" : __DIR__"andao2",
	]));
	setup();
}
