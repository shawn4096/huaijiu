// mu2.c
// Ĺ

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "Ĺ��");
	set("long",@long
�����ǹ���Ĺ�µ�Ĺ�ҡ�Ĺ�Ҳ���������һ�߰���ʯ�ף��Ա߷���һյ
�����ơ�ʯ��һ����Ⱦ�������������˽�����ɨ��
long);
set("exits", ([
"up" : __DIR__"mu",
]));
setup();
	set("count", 5);
}
void init()
{
	add_action("do_na", "na");
	add_action("do_move", "move");
	add_action("do_move", "open");
}
int do_move(string arg)
{
	object me, tmp;
	int dex;

	me = this_player();
	if (me->is_busy() || me->is_fighting()) return notify_fail("����æ���ģ�\n");

	if (arg != "coffin") return notify_fail("��Ҫ��ʲô��\n");
	
	message_vision("$N��������˫������ȥ�����ʯ�׸ǡ�\n", me);
	message_vision(HIR"��Ȼ�伸֧�̼��ӹ׺�һ���������������ֱ����$N�����ţ�\n"NOR, me);

	dex=me->query_dex() + me->query("kar");
	if( random(dex) < 0 && !me->query("hanshui_food") ) {
		message_vision(HIW"$N��æ���������û�ܶ��ȥ��\n"NOR, me);
		me->unconcious(); 
		me->set_temp("last_damage_from","�޶�����");
		me->die();
		if (tmp = present("corpse", this_object())) {
			object *ob = deep_inventory(tmp);
			int i = sizeof(ob);

			while (i--) if (userp(ob[i])) ob[i]->move(this_object());
			destruct(tmp);
			if (me) tell_room(this_object(), me->name()+"��ʬ�Ƕ��Ҳ����ˡ�\n");
		}
		return 1;
	} else {
		message_vision(HIW"$Nͷһ�ͣ��ܿ��̼����ƿ��׸ǡ�\n"NOR, me);
		me->set_temp("marks/��", 1);
		return 1;
	}
}

int do_na(string arg)
{
	object me, ob;

	me = this_player();
	if (me->is_busy() || me->is_fighting()) return notify_fail("����æ���ģ�\n");
	ob = this_object();

	if (arg != "all from coffin") return notify_fail("��Ҫ��ʲô��\n");

	if (!me->query_temp("marks/��")) return notify_fail("�㲻��ʯ�׵ĸ��ӣ���ô��������Ķ�����\n");

	if( random(30) > 15 || me->query_temp("marks/��") ) {
		write("����ʯ�������˰��죬ʲôҲû���õ���\n", me);
		write("ֻ����ž��һ�����׸ǲ�֪��ô�ֺ����ˡ�\n", me);
		me->delete_temp("marks/��");
		return 1;
	}
	if (ob->query("count") > 0) {
		switch(random(2)) {
			case 0: { 
				new("/d/emei/obj/yangpi")->move(me);
				write("���ʯ�����ó�һ��ɽ��Ƥ��\n", me);
				break;
			}
		}
	if (me->query_temp("emjiuyin")) {
		switch(random(10)) {
			case 1: {
				new("/d/emei/obj/yuzhuo")->move(me);
				write("���ʯ���ó�һ֧������\n", me);
				me->delete_temp("emjiuyin");
				break;
			}
		}
	}
		write("ֻ����ž��һ�����׸ǲ�֪��ô�ֺ����ˡ�\n", me);
		me->delete_temp("marks/��");
		me->set_temp("marks/��", 1);
		ob->add("count", -1);
	}
	return 1;
}
