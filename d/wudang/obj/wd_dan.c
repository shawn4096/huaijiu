// OBJ : /u/lius/obj/wd_dan.c �����µ�
// By lius 99/9

#include <ansi.h>
inherit ITEM;

string *eat_msg = ({
HIG"\n������ڼ�������������$N����һ����Դ�ɵ�����𣬱����澭������
һ����������\n" NOR,
HIM"\n$N����һ�ŵ��裬����һ��һ���������������ζ������������У�����ͷ���ٻ��Ѩ��
$Næ�����������������������չ鵤�����������\n" NOR,
HIC"\n������ǣ�$N�پ���ʹ�ޱȣ�����Ѫ�����ͣ���֫�ٺ���ӯ���ѣ�$Næ�����������࿹��
���ã�������Ϣ��˿������ԴԴ���ϣ������������٣�\n"NOR,
});
string *clr = ({RED"",GRN"",YEL"",BLU"",MAG"",CYN"",WHT"",HIR"",HIG"",HIY"",HIB"",HIM"",HIC"",HIW""});

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name( (clr[random(sizeof(clr))])+ "������ҩ" NOR, ({"wudang danyao","dan"}));
        set_weight(6); 
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���䵱���Ƶĵ��裬��˵����ͨ�񣬷��ϻ�ͯ��\n");
                set("value", 1000);
                set("no_drop", "�������������뿪�㡣\n");
                set("no_get", "�����������ò��ˡ�\n");
                set("no_give", "�����������������ˡ�\n");
                set("no_put", "�����������ܷ������ֶ������档\n");

        }

        setup();
}

int do_eat(string arg)
{
        int i,j,z;
//        int p
        string msg;
        object me = this_player();        
        if (!id(arg))
        return notify_fail("��Ҫ��ʲô��\n");
        
        z = random(10) + 1;
        if ( z  ) {
        msg = eat_msg[random(sizeof(eat_msg))];
        i = (int)me->query("medicine",1)*random((int)me->query("age",1)/5+10);
        j = 200+random((int)me->query("wd_job",1)/5);
        if (j > 400) j = 400;
        message_vision(msg, me);
        me->add("combat_exp",j);
        destruct(this_object());
        return 1;
        }
/*
        if ( 4 < z && z < 22 ) {
        i = (int)me->query("medicine",1)*random((int)me->query("age",1)/20+5);
        p = 250+random(100+(int)me->query("wd_job",1)/10);
        if (p > 350) p =350;
        message_vision(HIY"$N����һ�ŵ�ҩ������һ���죬ֻ�������泩�ޱȡ�\n"NOR, me);
        me->add("combat_exp",p);
        destruct(this_object());
        return 1;
        }
        if ( 1 < z && z < 3 ) {
        message_vision(HIB"\n$N����һ�ŵ���,ֻ��һ�ɶ������ؼ�����Ѩ���֣�ֱ�Ƶ��$Næ��ָ�Ե�����Ѩ��
�����������³�һ����Ѫ�������ް�������ȴ��������\n"NOR,me);
        me->add("combat_exp",-random(60));
        me->receive_damage("qi", me->query("max_qi")/12,"��ʳ��ҩ,�ж�����");
        me->receive_wound("qi", me->query("max_qi")/12,"��ʳ��ҩ,�ж�����");
        destruct(this_object());
        return 1;
        }
        if ( z < 2 ) {
        message_vision(HIR"\n$N����һ�ŵ���,�������ڽ�ʹ���������ң���Ҫ�˹��࿹�����ǲ���������\n"NOR,me);
        me->add("combat_exp",-random(120));
        me->receive_damage("qi", me->query("max_qi")/8,"��ʳ��ҩ,�ж�����");
        me->receive_wound("qi", me->query("max_qi")/8,"��ʳ��ҩ,�ж�����");
        me->receive_damage("jing", (me->query("max_jing")/8),"��ʳ��ҩ,�ж�����");
        me->receive_wound("jing", (me->query("max_jing")/8),"��ʳ��ҩ,�ж�����");
        me->unconcious();
        destruct(this_object());
        return 1;
        }
*/
        else   {
        message_vision(YEL"$N����һ�ŵ���,����ҩ��ƽƽ���������档\n"NOR,me);
        me->add("combat_exp",-random(20)+10);
        destruct(this_object());
        return 1;
        }
        return 1;
}

