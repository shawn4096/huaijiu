//����ϵͳ֮�鼮ƪ

#include <ansi.h>
inherit ITEM;

string long();

void create()
{
        set_name(NOR + WHT "�����ƪ" NOR, ({ "guwu book","book" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set_weight(300);
                set("unit", "��");
                set("long", "����һ�Ų�ȱ��ȫ����ҳ��\n" NOR);
                set("value", 30);
                set("no_cun", 1);
                set("no_sell", "ʲô��������һ����ֽͷҲ������Ǯ��");
                set("material", "paper");
                set("cloned",0);
               
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
                      "ͷС�֣��ƺ����Ϳ��ּ����йأ�\n��������Ŷ���(read)����Ҳ�����ѧ�ܹ�"
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

        if (arg && id(arg))
        {
                message_vision(HIW "$N" HIW "�۾�������Ķ���" NOR + na + HIW
                               "���������صĶ������ƺ������ջ�\n" NOR, me);
                if (!me->query("sjsz_guwu")) me->set("sjsz_guwu",1);
                me->add("sjsz_guwu", 5);
                tell_object(me, HIY "��ֻ����ǰ���ڵ�������ʻ�Ȼ���ʣ��Կ��ּ��������µĸ���\n" NOR);
                destruct(this_object());
                return 1;
        }
}
