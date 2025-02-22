// damen.c
// Modify By River 98/10
#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "大门");
        set("long", @LONG
这里是武馆的大门，两扇黑漆漆的大门敞开着，门口正中央高悬着一块黑
底金字的大匾“襄阳武馆”，台阶两旁立着两个石狮，你从大门口瞧进去，里
面好象人来人往，都很忙碌的样子。门口站着两个门卫，神情威严。
LONG
        );      
                 
        set("outdoors","武馆");
 
        set("no_fight", 1);
 
        set("exits", ([
               "south" : "/d/xiangyang/eroad1",
               "enter": "/d/wuguan/menlang",
        ]));
        
        set("objects", ([
                "/d/wuguan/npc/menwei" : 1,
        ]));

        set("coor/x",10);
 set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",10);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}


int get_object(object ob)
{
        if(userp(ob))
        return 1;
        return 0;
}
 
int valid_leave(object me,string dir)
{
     object *inv = deep_inventory(me);
     object *obj;          
     if( me->query_temp( "wg_help" ) || me->query_temp( "wg_road" ) == 2 )
          return notify_fail("武馆门卫说道：" + RANK_D->query_respect(me) +
                        "还是再耐心等一会吧，说不定马上就有人来仗义帮助。\n");                      
     if( me->query_temp( "wg_juanzeng" ) )
          me->delete_temp( "wg_juanzeng" );
     if( me->query_temp( "wg_road" ) == 1 )
          me->delete_temp( "wg_road" );
     if( me->query("combat_exp") > 3000 && dir == "enter")
         return notify_fail("门卫上前把手一伸：你的武功够高了，在武馆学不到什么了。\n");
//      if( !me->query("enter_wuguan") && dir == "enter")
//         return notify_fail("门卫把手一伸：你已经离开武馆了，就不能进去了。\n");
     obj = filter_array(inv,(:get_object:));
     if( sizeof(obj) && dir =="enter" )
         return notify_fail("门卫朝你嘿嘿一笑:想带谁偷偷进武馆啊？\n");
         return ::valid_leave(me, dir);
}
