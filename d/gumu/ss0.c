// ss0.c By River 98/08
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{ 
       set("short",HIB"石室"NOR);
       set("long", @LONG
头顶的石壁(shibi)又恢复了原状，你发现自己置身于一间阴沉的石室中，
空荡荡的感觉使你心中只有恐惧，甚至忘记孤独。你不知身处何地，四周如此
漆黑一片，只能靠摸索前行。
LONG
     );
        set("item_desc", ([         
            "shibi": "石壁恢复了原状，与周围吻合地天衣无缝，你不由感叹其高超造诣。\n"NOR,
        ]));

        set("exits", ([
              "out" : __DIR__"ss1",
        ]));

        setup();
}

void init()
{
        add_action("do_tui", "tui");      
}

int do_tui(string arg)
{
        object me=this_player();
        if (me->is_busy() || me->is_fighting())
              return notify_fail("你正忙着哪！\n");
        if (arg =="shibi"){
           message_vision(YEL"$N双手把石壁用力向上推去，咯吱吱一声，石壁缓缓移开。\n"NOR,me);
           set("exits/up", __DIR__"gmws1");
           remove_call_out("close");
           call_out("close", 5, this_object());
           return 1;  
        }
        return notify_fail("你要推什么？\n");
}

void close(object room)
{
        message("vision",HIY"石壁慢慢移了回来，恢复了原状。\n"NOR, room);
        room->delete("exits/up");
}
      