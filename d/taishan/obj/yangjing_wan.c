// yangjing_wan ������

inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("������", ({"yangjing wan", "jing", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "һ���ںڷ�����Сҩ�衣\n");
              set("medicine", "drug");
                set("value", 5000);
        }
        setup();
}

int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("��Ҫ��ʲôҩ��\n");
        if ((int)this_player()->query("eff_jing") == 
            (int)this_player()->query("max_jing"))
                return notify_fail("�����ڲ���Ҫ�������衣\n");
        else {
                this_player()->receive_curing("jing", 20);
                message_vision("$N����һ�������裬��ʱ���Ϸ����˺���\n", this_player());
                destruct(this_object());
                return 1;
        }
}

