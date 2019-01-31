// lagoon.c ��ʯ
// By Looklove for a Quest
//Last change at 2k/5/27 by Looklove

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short",HIC"��ʯ"NOR);
	set("long", @LONG
���ǰ�������ͻ����һ���ʯ���������ƽ�����������ٿ���������
����ʮ�ˡ������ĺ�ˮһ�δγ������������г���Ĵ�������ֻ��֪���ĺ���
���������Ͽգ����˴��ų�����ڸ����Ľ�ʯ�ϡ�һ˿�������Ʋ����赭д��
Ĩ��Զ��������У��·�һ��ˮī����ż���м�ֻ�������С���ˮ��Ӻ�ˮ
�����������������ߵĽ�ʯ�ϡ�
LONG
	);
	set("outdoors","����");
	set("exits",([
		"westdown" : __DIR__"island5",
	]));
	setup();
}

void init()
{
	add_action("do_fish","fish");
	add_action("do_fish","diaoyu");
	add_action("do_nosleep","sleep");
	add_action("do_shou","shouxian");
	add_action("do_nosay","say");
}

int do_fish()
{
	object me = this_player();

	if (me->is_busy()) return notify_fail("��������æ���أ�\n");
	if (present("yu",  environment(me)))
		return notify_fail("�����Ѿ���ô�����ˣ���Ҫ�������ﰡ��\n");
	if (!present("yu gan", me))
		return notify_fail("��Ԩ���㣬�����˶�������û����ͣ�������ô��������\n");
	if (me->query("jingli") <200 )
		return notify_fail("�����̫���ˣ����Ǹ����ٵ��ɡ�\n");
	if (me->query_temp("gb/fish"))
		return notify_fail("�����߰ɣ�����ҧ����Ĺ��ء�\n");
	if (present("hai gui", me) && (random(me->query("jingli"))<500)) {
		message_vision(HIG"$N�����������Ҫ���߳�ȥ��һֻ�󺣹���������������"+
			"��$N�Ľ���ҧ��һ�ڡ�$N�۵�����������\n"NOR, me);
		me->receive_wound("qi", random(100), "������ҧ");
		me->start_busy(5);
		return 1;
	}

	message_vision("$N��������ڹ��ϣ�һ�����е���ͣ�����˦�˳�ȥ��\n", me);
	me->receive_damage("jingli", 20);
	me->start_busy(2);

	if (!random(4)) {
		write(HIC"��ͻȻ�����������һ���������Ϲ��ˣ�������(shouxian)����\n"NOR);
		me->set_temp("gb/fish",1);
	} else write("ֻ����Ưһ����һ��С��������Ե��ˡ��㽫�չ�ק��������\n");
	return 1;
}

int do_shou()
{
	object me = this_player();
	object ob,ob1,ob2;

	ob=present("yu gan",me);
	ob2=present("yu",me);

	if (!me->query_temp("gb/fish")) return notify_fail("��˦�;������ߣ��и��ԣ�\n");
	if (me->is_busy()) return notify_fail("�𼱣���������\n");
	if (me->query("jingli") <200 ) return notify_fail("�����̫���ˣ����Ǹ����ٵ��ɡ�\n");
	me->delete_temp("gb/fish");
	if (me->query("mud_age")*2 >= me->query("combat_exp"))
		return notify_fail("�㻹�Ƕ໨��ʱ�������ɣ�����书�ķ��ˡ�\n");
	if (!ob) return notify_fail("�������أ�\n");
	if (random(me->query("str"))<5 && !random(6)) {
		message_vision(HIY"ͻȻ$N�ĸ����Ҷ��������������������㡣\n"
			"$N����ק���᲻�����֣���������˴��ͳ����˺��\n"NOR,me);
		destruct(ob);
		if (random(me->query("kar"))>2 && random(10)>1) {
			message_vision(HIG"$Nһ�١����١����ò��������ϰ���������δ����ڴ�ڴ��Ŵ�����\n"NOR, me);
			me->set("water", me->max_water_capacity()+200);
		} else me->unconcious();
		return 1;
	}
	me->receive_damage("jingli", 100+random(50));
	me->start_busy(1);
	if (ob2 && (random(me->query_str()) <20)) {
		write(HIC"��������͵Ĺ���һ��������ֱ��ֱĽ���ˮ�\n"NOR);
		destruct(ob2);
		return 1;
	}
	if (random(me->query("combat_exp")) > 200000 && random(me->query_int())> 4)
		if(me->add("potential",10+random(10)) > me->query("max_pot")*2)
			me->set("potential", me->query("max_pot")*2);
	if (random(me->query_str()) > 20 && random(me->query("kar")) < 5)
	{
		message_vision("$N�������ͣ����ž��һ�����ˡ�\n", me);
		destruct(ob);
		new("/d/gb/obj/yugan2")->move(me);
		return 1;
	}
	if (random(me->query("kar")) < 5 && !random(8)) {
		message_vision(HIG"$N��������ק�����������ֹ��������һֻ�Ʋ�Ь��\n"
			"$N�����ƿڴ������������ĸ����˵����Ӳ�Ь������\n"NOR, me);
		return 1;
	}
	message_vision(HIG"$N�����ؽ�һ��������ק��������\n"NOR, me);
	ob1=new("/d/gb/obj/fish"+(1+random(7)));
	ob1->move(this_object());
	return 1;
}

int do_nosleep()
{
	object me = this_player();
	if (me->is_busy())
	return notify_fail("��������æ���أ�\n");
	write("���ﺣ��ܴ�С�����������ĵ���ĵط�˯�ɡ�\n",me);
	return 1;
}
int do_nosay()
{
	write("�ꡭ����˵��,���㶼�����ˡ�\n");
	return 1;
}
