// /u/dubei/miaojiang
// by dubei

inherit ROOM;

void create()
{
        set("short", "山洞");
        set("long", @LONG
这里四周黑漆漆的，身手不见五指。隐隐约约的看到四壁上爬满了树藤。
地上的路面高低不平，让你心升惧意。
LONG
        );

        set("exits", ([
              "out" : __DIR__"slu9",
               
             ]));
      
 
        set("outdoors", "miaojiang");
        setup();
}

void reset()
{
        if (!random(2)) set("xuezhu_count", 1);
}

void init()
{
        add_action("do_dian", "dian");
        add_action("do_yao", ({ "zuan", "yao" }));
} 
int do_dian(string arg)
{ 
         object me;
        me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me))  return 0;
        if( arg=="fire" ) {
             write(
             "\n你点燃了火折，借着光亮你看到洞的四壁全是树藤，树藤 
的空隙中布满了雪白的蜘蛛网。\n"
             );
            me->set_temp("mark/点", 1);
             return 1;
         }
}
int do_yao(string arg)
{
        object me;
        me = this_player();
        if ( !arg || arg != "shuteng" )
        return notify_fail("你要干什麽？\n");
        if (!me->query_temp("mark/点"))
        return notify_fail("你要干什麽？\n");
           if (query("xuezhu_count") > 0) 
          {
           message_vision("$N轻轻摇晃树藤，忽然掉下一只雪蛛。\n", me);
           add("xuezhu_count", -1);
           new(__DIR__"npc/xuezhu")->move(__DIR__"shandong",);
           me->delete_temp("mark/点");
          }
        else
           message_vision("$N晃动了半天，发现什麽也没有。\n", me);
     return 1;
}
