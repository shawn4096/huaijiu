// hhs		�����ϻ�ɢ
// 2/9/2k  by emnil

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIB"�����ϻ�ɢ"NOR, ({ "hehuan san","san" }) );
        set("long",HIB"����Ѫ���������Ƶ�ҩ�ۣ�ֻ��Ҫ��(sa)һ�����ܷ������á�\n"NOR);
        set("unit", "��");
        set("weight", 90);
        set("no_sell",1);
        set("value", 0);
}

void init()
{
	add_action("do_sa","sa");
}

int do_sa(string arg)
{
	object me=this_player() , ob , bb;

	if (!arg) return notify_fail("��Ҫ��˭��\n");

	ob = present(arg, environment(me));
	if (!ob || !living(ob)) return notify_fail("��Ҫ��˭��\n");

	if (!wizardp(me) && ob->query("gender")!="Ů��" )
		return notify_fail("��û�и��ѽ������ɲ������ӣ�\n");
	
	if (!wizardp(me) && (userp(ob) || ob->query("id")!="beauty"))
		return notify_fail("���Ů�˺���������Ҫ���Ǹ�����\n");

	bb=present("body guard", environment(me));
	if(!objectp(bb) || bb!=ob->query("guard"))
		bb=present("super guard", environment(me));
	if(objectp(bb) && bb==ob->query("guard"))
		return notify_fail("�˼��б������أ�����ô��̫ð���˰ɣ�\n");

	if( objectp(ob->query("guard")) )
		return notify_fail("hmm�����ƺ�������BUG��\n");
        if(me->query("xs/girl_ob") != ob)
                return notify_fail("�����������ץ��������\n");

	if (!ob->query("ok"))
		ob->kill_ob(me);
	message_vision(HIB"$N"HIB"�ٺ���Ц�˼�������ָ����$n���ᵯ�˵��ĭ��\n"
			MAG"��һ�����$n������ͨ������˹�ȥ��\n"NOR,me, ob);
	message_vision("\nֻ���߳�����׳�����ӽ�$N��������ѩɽ�ķ��򼲱���ȥ��\n", ob);

//	ob->unconcious();
//	ob->set("hhs",1);
//	ob->set_leader(me);
	if (me->query("xs/girl_ob") == ob)
		me->set_temp("xs/finish", 1);
/*
	if (wizardp(me))
		ob->unconcious();
	else
*/		destruct(ob);
	return 1;
}
