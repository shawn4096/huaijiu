// kuloutou.c ����ͷ

inherit ITEM;

void create()
{
        set_name("����ͷ", ({ "kulou tou" }) );
        set_weight(1500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 30);
                set("long", "����һ������ͷ�����������ָ�����㲻���뽫��ָ����(insert)��ȥ��\n");
                set("no_cun", 1);
                set("no_give", 1);
		set("no_get", "�������������뿪�Ƕ���\n");
		set("treasure",1);
                set("degree",1);
                set("no_drop", 1);
                set("credit",50);
                set("desc","����һ�ξ����½���ʧ�ܼ�¼�ĸ�����Ʒ��");
               
        }
        setup();
}

void init()
{
    add_action("do_cha",({"cha","insert"}));
}

int do_cha(string arg)
{
    object me=this_player();

    if( !arg ) return 0;

    if( arg!="kulou tou" && arg!="����ͷ" ) return 0;
       
    if( me->is_fighting() || me->is_busy() )
            return notify_fail("����æ���ء�\n");

    if( !me->query("jiuyin/chenfail") )
            return notify_fail("��֮ǰ�й�ʧ�ܼ�¼��\n");

    message_vision("$N�������ָ��������ͷ�ϵ����ָ�ס�\n", me);

    tell_object(me, "���Ȼ���������ָ���ò����ָ�ף����ﲻ�������ز���һ��а�\n");

    me->add("jiuyin/chenfail", -1);
            
    tell_object(me, "�������ָ�ݺݽо�����������ͷ�����������ˡ�\n");
    
    message_vision("$N��ָ�о���ֻ����һ�����죬��������ͷ����$N����÷��顣\n", me);

    destruct(this_object());

    return 1;
    }
