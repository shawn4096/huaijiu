// Room: /d/huashan/jinshe/obj/datiehe.c
// Date: Look 99/03/25

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("������" , ({ "tie he", "box" }) );
        set_weight(3000);
        set_max_encumbrance(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���������ߵ������ӣ�����������������\n");
                set("value", 1000);
                set("material", "steel");
                set("no_get",1);
                set("no_drop",1);
                set("amount",30);
                }
        setup();
}

int is_container() { return 1; }

void init()
{
        add_action("do_open", "open");
        add_action("do_move", "move");
}

int do_open(string arg)
{
        object me = this_player();
        object ob;

       
    if (!arg || (arg != "box" && arg != "tie he"))
       {
        return notify_fail("�����ʲô��\n");
        return 1;
       }
    else
    {
    if (!present("xin jian",me))
       {
        write("���Ὺ��ϻ��ͻȻ������һ���ż㣬�㼱æ��������\n");
        ob=new(__DIR__"xinjian1");
        me->set_temp("mark/open",1);
        ob->move(me);
        return 1;
       }
        write("������У���������տյ�ʲôҲû�С�\n");
        return 1;
    }
}
int do_move(string arg)
{
        object me = this_player();
        
        if ( !arg || arg != "anceng" )
        return notify_fail("��Ҫ��ʲ�᣿\n");
        if (!(int)me->query_temp("mark/open"))
         return notify_fail("��Ҫ��ʲ�᣿\n");
        message_vision(RED"$NͻȻ���������������棬���һ����һ��鴤��\n"NOR, me);
        me->delete_temp("mark/open"); 
        me->set_temp("last_damage_from", "�ж�");
        me->die();
        return 1;
}
