#include <ansi.h>

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "书场");
        set("long",@long
你走进书场，看见里面热热闹闹的，场子里都是听书的，场子前面有一
位说书先生，他看上去四五十岁，手中拿着一块响板，正在聚精会神地说着
评书---《杨家将》。你也逐渐北评书的内容所吸引，场中的人们不时的发出
惊叹和喝彩声，时不时将铜板抛了上去。
long);
 set("item_desc", ([
    "door" :
"这是一扇通往后堂的小木门。\n"
]));
set("objects",([
__DIR__"npc/gongzige" : 1,
]));
set("exits",([
"enter" : __DIR__"houtang",
"south" : __DIR__"xidajie2",
]));
set("no_clean_up", 0);
create_door("enter", "小门", "out", DOOR_CLOSED);
set("coor/x",90);
  set("coor/y",-200);
   set("coor/z",0);
   setup();
}
