// jiedu-dan.c

#include <ansi.h>

inherit ITEM;

void init()
{
             add_action("do_eat", "fu");
}

void create()
{
        set_name("���Ľⶾ��", ({"jiedu dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","����һ����ò����ĵ�ҩ��ȴ�ɽ�ٶ���\n");
                set_weight(25);
                set("value", 10);
                set("unit", "��");

        }
}

int do_eat(string arg)
{
        object me;
        int i,plvl,cure;
        mixed a;
        mapping fam;
        string poison;
        a = ({"snake_poison","xx_poison","dsy_poison","fs_poison","huagu_poison","man_poison","qinghua_poison","qishang_poison","qzhu_poison","sl_poison","sy_poison","warm_poison","hot_poison","cold_poison","bing_poison","hb_poison","bt_poison"}); 
        me = this_player();
        for( i=0; i < sizeof(a); i++ )
                        if( me->query_condition(a[i]) > 0 )
                        {
                                poison = a[i];
                                break;
                        }
        if (!id(arg)) return 0;

        plvl= me->query_condition(poison , 1);

        if( plvl == 0 )
                return notify_fail("�㲢û�ж���С�ĳԴ���ҩ��\n");


        message_vision(MAG"\n$N����һ�����Ľⶾ�����е��������о綾�Ѿ���ҩ������ɢ��\n\n"NOR , me);

        me->apply_condition(poison, 0);

        destruct(this_object()); 
        return 1;
}