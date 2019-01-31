// quit.c

#include <ansi.h>
#include <command.h>

inherit F_DBASE;

void do_quit(object, int);

void create()
{
	seteuid(getuid());
	set("channel_id", "����ָ��");
}

int main(object me, string arg)
{
	object link_ob, env;
	int flag = 0;

	if (interactive(me) && query_idle(me) < 2 && me->query_temp("quit") > uptime())
		return notify_fail("�����˳������У����Ժ�\n");
	link_ob = me->query_temp("link_ob");

	// We might be called on a link_dead player, so check this.
	if( link_ob ) {
		// Are we possessing in others body ?
		if( link_ob->is_character() ) {
			write("��Ļ��ǻص�" + link_ob->name(1) + "�����ϡ�\n");
			exec(link_ob, me);
			link_ob->setup();
			return 1;
		}
		link_ob->set("last_on", time());
		link_ob->set("last_from", query_ip_name(me)+"("+query_ip_number(me)+")");
		link_ob->save();
	}

	if (this_player(1) == me && interactive(me)) {
		if (me->query_condition("killer")&&!wiz_level(me)) return notify_fail("��������ͨ���������Զ�ܵ���ʵ������ȥ��\n");
		if(me->is_ghost()) return notify_fail("�������Ĺ�겻�ܹ��ܵ���ʵ����ȥ���ˡ�\n");
		if( me->is_busy()) return notify_fail("��������æ���������£������˳���Ϸ��\n");
		if( me->is_fighting()) return notify_fail("����������ս���������˳���Ϸ��\n");
	} else flag = -1;

	if ((env = environment(me)) && !env->query("no_save") && !me->is_ghost() && !clonep(env))
		me->set("startroom", base_name(env));

	me->set_temp("quit", uptime() + 203);
	CHANNEL_D->do_channel(this_object(), wiz_level(me)?"wiz":"sys", me->short() + NOR " ׼���뿪��Ϸ�ˡ�");
	if (!flag && !wizardp(me) && env && !env->query("valid_startroom")) {
		write("�����˳���Ϸ����\n");
		me->delete_temp("combat_yield");
		call_out("do_quit", 3, me, 100);
	} else do_quit(me, flag);

	return 1;
}

void do_quit(object me, int t)
{
	int i, j;
	object link_ob;
	object *inv;

	if (!me) return;
	if (t > 0 && (!living(me) || me->is_busy() || me->query_temp("combat_yield") || me->is_fighting())) {
		me->delete_temp("combat_yield");
		call_out("do_quit", 2, me, t - 1);
		return;
	}
	if (t >= 0 && (me->query("qi") < 0
	|| me->query("eff_qi") < 0
	|| me->query("jing") < 0
	|| me->query("eff_jing") < 0
	|| me->query("jingli") < 0)
	) {
		message("channel", "��Ϊ����ǰ��״̬���ȶ����˳������Զ���ֹ��\n", me);
		return;
	}
	if( !wiz_level(me) ) {
		inv = all_inventory(me);
		for(i=0; i<sizeof(inv); i++){
			if( !inv[i]->query_autoload() && !inv[i]->query("unique") )
				DROP_CMD->do_drop(me, inv[i]);
		}
	}
	if( me->query_team()) me->dismiss_team();

	i = uptime()-me->query_temp("time");
	tell_object(me, HIW"\n���齣����"NOR"�������ܹ�����"+CHINESE_D->chinese_time(i)+"��\n");
	i = me->query("combat_exp") - me->query_temp("combat_exp");
	tell_object(me, "\t  ����ֵ"+(i < 0?"������"+(-i)+"��":i > 0?"������"+i+"��":"û�б䶯")+"��\n");
	me->update_age();
	if (me->query("online_total") > 70200)
		tell_object(me, "\t  �������Ϣ"
			+CHINESE_D->chinese_time(me->query("online_total")/3+3600)
			+"������\n");
	else
		tell_object(me, "\t  ��ӭ���´�������\n");

	if (!wizardp(me) && me->query_temp("robottest") <= me->query_temp("time")) {    // ���û���ܵ��������˼��
		if (me->add("no_robot_check", 1) > 1) {
			me->add("online_total", 7200);
			me->delete("no_robot_check");
		}
	} else me->delete("no_robot_check");

	message("system", me->name() + "�뿪��Ϸ��\n", environment(me), me);

	CHANNEL_D->do_channel(this_object(), wiz_level(me)?"wiz":"sys", me->short(1) + NOR " �뿪��Ϸ�ˡ�");
	log_file( "USAGE", sprintf("%-19s%s�˳�(%s)\n",
		me->query("name")+"("+capitalize(""+me->query("id"))+")",
		interactive(me)?"":"����",
		ctime(time())[4..18])
	);

	if (link_ob = me->query_temp("link_ob")) {
		link_ob->set("last_on", time());
		link_ob->set("last_from", query_ip_name(me)+"("+query_ip_number(me)+")");
		link_ob->save();
		destruct(link_ob);
	}

	i = (me->query("mud_age") - me->query_temp("mud_age")) / 60;
	if (!wiz_level(me) && i
	&& (j = (me->query("combat_exp") - me->query_temp("combat_exp"))
		/ i) > 100)
		log_file("static/EXP",
			sprintf("%s %s �ϴξ��飺%d�����ξ��飺%d��ƽ����%d/�֣�����ʱ��Ϊ %d �֡�\n",
				ctime(time())[4..18], geteuid(me), me->query_temp("combat_exp"),
				me->query("combat_exp"), j, i)
		);

	TOP_CMD->add_rank(me);
	me->save();
	destruct(me);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : quit

��������ʱ�뿪��Ϸʱ, �����ô�ָ�
HELP
    );
    return 1;
}
