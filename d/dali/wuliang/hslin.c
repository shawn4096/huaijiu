// Room: hslin.c
// By River 98/12
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "黑森林");
        set("long", @LONG
你快步而行，只见迎面黑压压的一座大森林。走近前去，只见左首一排九
株大松树参天并列，好象有些异样。 
LONG
        );
        set("exits", ([
            "south" : __DIR__"tiesuo",
        ]));
 
        set("outdoors", "大理");

        set("coor/x",-280);
  set("coor/y",-270);
   set("coor/z",-20);
   setup();
}

void init()
{
        add_action("do_enter","enter");
}

int do_enter(string arg)
{
        object me=this_player();
        if ( !arg ) return 0;
        if ( arg=="第四株" ){
        write(HIW"\n你绕到第四株树后，拨开长草，树上出现一洞，你钻进树洞，左手拨开枯草，\n"+
              "右手摸到一个大铁环，用力提起，木板掀开，下面便是一道石级。走下几级，\n"+
              "双手托着木板放回原处，沿石级向下走去，三十余级后石级右转，数丈后折而\n"+
              "向上，上行三十余级，来到平地。\n\n"NOR,me);
        me->move(__DIR__"caodi");
        return 1;
        }
       return 0;
}
