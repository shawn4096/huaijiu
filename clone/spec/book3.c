//����ϵͳ֮�鼮ƪ

#include <ansi.h>
inherit ITEM;

string long();

void create()
{
        set_name(NOR + WHT "��ɽ����ƪ" NOR, ({ "songshan book" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set_weight(300);
                set("unit", "��");
                set("long", "����һ�Ų�ȱ��ȫ����ҳ��\n" NOR);
                set("value", 30);
                set("no_cun", 1);
                set("no_give", 1);
                set("no_drop", 1);
		set("no_get", "�������������뿪�Ƕ���\n");
		set("treasure",1);
                set("material", "paper");
                set("degree",1);
                set("credit",50);
                set("desc","ȫ��������ɽ�����Ľ�����Ʒ��");
               
        }
        setup();
}

void init()
{
	add_action("do_read","read");
}

string long()
{
        string msg;

               msg = "����һ��" + name() + NOR + "��������"
                      "�Ѿ�������ʱ�ˡ�\nҳƬ����������������д����Ӭ"
                      "ͷС�֣�������һЩ����ɽ��������֮���������йص����ݣ�\n��������Ŷ���(read)����Ҳ�����ѧ�ܹ�"
                      "����������\n";


        return msg;
}

int do_read(string arg)
{
        object me = this_player();

        int na = this_object()->name();
      
        if (me->is_busy())
                return notify_fail("����������æ��\n");

        if (me->is_fighting())
                return notify_fail("ս�����޷��ж���֪��\n");

        if (me->query("ss/pass_deng"))
                return notify_fail("�㶼ѧ���ˣ�����֪��ʲô��\n");

        message_vision(HIW "$N" HIW "�۾�������Ķ���" NOR + na + HIW
                               "���������صĶ������ƺ������ջ�\n" NOR, me);

        tell_object(me, HIY "��ʼ���޷���͸ҳƬ���������ݣ�����ҳƬ�ϲ����ἰ�ĵ˰˹�(Deng bagong)���������ע�⡣\n" NOR);
        me->set_temp("ss/zsb_0",1);
        destruct(this_object());
        return 1;

}
