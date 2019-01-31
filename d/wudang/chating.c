// /d/wudang/chating.c ��ͤ
#include <ansi.h>
inherit ROOM;


void create()
{
        set("short", "��ͤ");
        set("long", @LONG
��������·���Ա߶����Ĳ�ͤ��������裬��������Զ���ķ羰��
������ν͵�ø���������! û�б�����õ�Ъ�ŷ����ˡ�ͤ�������
Ⱥ������Χ������(table)����������(chair)�ϣ��е����ģ��еĳ�
�����ò���ң���ڡ�
LONG
        );

        set("exits", ([
                "northwest" : "/d/wudang/wdroad8",
        ]));
        
    set("item_desc", ([
            "table" : "һ�ŵ��ŵ���ľС�����������ˮ���̺��������ߡ�\n",
            "chair" : "һֻ������ƵĿ��Σ�����ȥҡҡ�λΣ������Ү��\n",
        ]));
                                        

        set("objects",([
                __DIR__"npc/taohua" : 1,
                __DIR__"obj/mitao" : 2,
                __DIR__"obj/xiangcha" : 1,
        ]));
        
        
        set("coor/x",40);
  set("coor/y",20);
   set("coor/z",0);
   setup();
}

void init()
{
        add_action("do_tap", "tap");
        add_action("do_tap", "knock");
        add_action("do_sit", "sit");
}


int do_tap(string arg)
{

        object me;
        object cui;

        if (!arg || (arg != "desk" && arg != "table"))
        {
                return notify_fail("��Ҫ��ʲô��\n");   
        }
                
        me = this_player();     
        if( !objectp(cui = present("tao hua", environment(me))) )
                return notify_fail("�����������ӣ�ȴ����û�����㡣��ͻȻ�о�һ��ʧ�䡣\n");
                                
        if( !me->query_temp("marks/sit") )  
                return notify_fail("�����������ӣ����е��˶���ͷ�Ȼ�ؿ����㣬"
                        +"\n��ͻȻ�о��Լ����޴���\n");
        
    if( me->query_temp("marks/served") )
    {
        message_vision("�һ����ͷ��ض�$N˵�����ո����Ϲ�������ž�Ҫ��"+
                                "���Ǹ���Ͱ���ǰ�?��\n", me);
        return notify_fail("");
    }

        message_vision("$N��������ǰ��������������棬�һ�һ˦С�磬�����к���\n", me);
        
        cui->serve_tea(me) ;

    me->set_temp("marks/served", 1);
//  remove_call_out("delete_served");
      call_out("delete_served", 300, me);

        return 1;
}


void delete_served(object me)
{
        if ( objectp(me) ) me->delete_temp("marks/served");
}


int do_sit(string arg)
{

        if ( !arg || (arg != "chair") )
                return notify_fail("��Ҫ��ʲô���棿\n");       
        
        if (this_player()->query_temp("marks/sit"))
                return notify_fail("���Ѿ����˸���λ�ˡ�\n");   
                        
        this_player()->set_temp("marks/sit", 1);
        return notify_fail("�����˸���λ���£������ϲ衣\n");   
}


int valid_leave(object me, string dir)
{

        if (  (dir == "north")
           && ( present("xiang cha", this_player())
                || present("mi tao", this_player()) ) 
           && objectp(present("tao hua", environment(me))) )
        switch ( random(2) ) 
        {
        case 0: 
         return notify_fail
                ("�һ�����һƲ���Ա��˺����˻����������߻��ﻹ����һЩ��СŮ��Ҳ���������أ�\n");
         break;
        case 1:
         message_vision("�һ���$N���˸��򸣣��峤�涨����ʳ���ô����跿��", me);
         return notify_fail("\n");
         break;
        }
        
        me->delete_temp("marks/sit");
        me->delete_temp("tea_cup");
        return ::valid_leave(me, dir);
}


