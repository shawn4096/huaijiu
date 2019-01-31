#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
    set("short", HIB "�﷿" NOR);
    set("long", "�������һ�����һ��С���䡣\n"
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
