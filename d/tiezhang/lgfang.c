//Room: lgfang.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIC"练功房"NOR);
       set("long", @LONG
这是一间用花岗岩砌成的石屋。室内一只大炉中燃了洪炭，煮着热气腾腾
的一镬东西，镬旁两个黑衣小童， 一个使劲推拉风箱，另一个用铁铲翻炒镬
中之物，听这沙沙之声，所炒的似是铁沙。几名帮中弟子闭目盘膝坐在锅前，
或对着腾上的热气吐呐，或插指于镬中苦练。
LONG
       );
       set("exits", ([ 
           "east" : __DIR__"guangchang",
       ]));

       set("objects",([
//           __DIR__"npc/heiyi" : 1,
       ]));

       set("item_desc", ([
           "huo" : "这是一口巨大的铁锅，锅中盛满铁沙，下面燃着炭火，是帮主练铁掌用的。\n",
       ]));

       set("coor/x",-340);
       set("coor/y",-260);
       set("coor/z",0);
       setup();
}

void init()
{
    add_action("do_chazhi", "chazhi");
}


int do_chazhi(string arg)
{       
    mapping fam;
    object me;
    me = this_player();

    if(!living(me)) return 0;
    if(!living(this_player()) || arg != "huo" )
      {
          write("你想往哪儿插呀！\n");
          return 1;
      }

    if(!(fam = this_player()->query("family")) || fam["family_name"] != "铁掌帮")
          return notify_fail("你非本帮弟子，不能在此练功！\n");

        if((int)me->query_skill("strike", 1) < 30) {
          write("你将双手插入镬中，显然，你受不了这铁沙的温度。\n");
          write("你觉得一股热气直逼上来，焦燥难当！\n");
          me->unconcious();
          return 1;
          }
          
    if((int)me->query_skill("strike", 1) > 120)
          return notify_fail("你将双手插入镬中，发现铁沙的温度对你来说太低，已毫无意义了。\n");
    
    if((int)me->query("qi")<30){
          me->receive_damage("qi",10);
          write("你觉得一股热气直逼上来，焦燥难当！\n");
          me->unconcious();
          return 1;
      }
        me->receive_damage("qi", 20+ random(20));
    me->improve_skill("strike", me->query("int"));
    message_vision("$N将双手插进镬中的铁沙里。\n", me);
    write("灼热的铁沙将你的双手烫得通红，你觉得双手变得强壮有力。\n");
    return 1;
}
