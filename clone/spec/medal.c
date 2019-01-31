#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + HIY "��ģѫ��" NOR, ({ "worker medal" }) );
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("value", 30);
                set("long", "����һö��ģѫ�£�ר��Ϊ�����Ƚ��Ͷ�ģ���������ģ�����Խ������(wear)����ǰ��\n");
                set("no_cun", 1);
                set("no_drop", 1);
                set("no_give", 1);
		set("no_get", "�������������뿪�Ƕ���\n");
		set("treasure",1);
                set("degree",1);
                set("credit",100);
                set("desc","�ۼ�1000������Ѳ����������ĸ�����Ʒ��");
               
        }
        setup();
}

void init()
{
    add_action("do_dai",({"dai","wear"}));
}

int do_dai(string arg)
{
    object me=this_player();

    if( !arg ) return 0;

    if( arg!="worker medal" && arg!="��ģѫ��" ) return 0;
       
    if( me->is_fighting() || me->is_busy() )
            return notify_fail("����æ���ء�\n");

    if( me->query("mingjiao_job")<1001 )
            return notify_fail("�㹤�������������������ģѫ�£�\n");

    message_vision("$N����ģѫ���������ǰ��\n", me);

    tell_object(me, "�㽫��ģѫ���������ǰ�����ﲻ�������س�������������\n");

    me->add("mingjiao_job", -1000);
            
    destruct(this_object());

    return 1;
    }
