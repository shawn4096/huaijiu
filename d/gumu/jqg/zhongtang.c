// zhongtang.c

inherit ROOM;
#include <ansi.h>

void create()
{
       set("short",HIC"中堂"NOR);
       set("long", @LONG
你举步走入一间茅屋的中堂，只见屋中陈设简陋，但洁净异常，堂上只有
一桌一几，此外便无别物。
LONG
        );

       set("exits", ([
          "out" : __DIR__"xiaolu",
          "east" : __DIR__"xiaoshi",
          "north" : __DIR__"wshi",
       ]));     
       setup();
}

void init()
{
       object me = this_player();
       if( me->query("family/family_name") =="古墓派"
       && !me->query("gumu/buchang")
       && me->query_skill("strike", 1) > me->query_skill("hand", 1)){
          me->set_skill("hand", me->query_skill("strike", 1));
          me->set("gumu/buchang", 1);
          tell_object(me,HIG"系统自动将你的「基本手法」等级补偿成「基本掌法」的等级。\n"NOR);
       }
}
