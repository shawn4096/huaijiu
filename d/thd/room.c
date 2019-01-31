#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
    set("short", HIB "箫房" NOR);
    set("long", "这里是桃花岛的一个小房间。\n"
);
    set("sleep_room",1);

    
    set("exits", ([
    "out" : __DIR__"jicui.c",        ]) );

    set("objects",([
       BINGQI_D("sword/biyuxiao") : 1,
       "/clone/weapon/tiexiao" : 1,
       "/clone/weapon/yuxiao" : 1,
       "/clone/weapon/xiao" : 1,
       BINGQI_D("sword/ziyuxiao") : 1,
       ]));
   
    setup();  
}
