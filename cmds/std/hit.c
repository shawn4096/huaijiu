// fight.c

#include <ansi.h>

int main(object me, string arg)
{
	object obj;

	if( environment(me)->query("no_fight") )
		return notify_fail("�����ֹս����\n");

	if(strsrch(file_name(environment(me)),"/d/wuguan/") >= 0)
		return notify_fail("����ڽ�ֹ���ˡ�\n");
		
	if(!arg || !objectp(obj = present(arg, environment(me))))
		return notify_fail("���빥��˭��\n");

	if( !obj->is_character() || obj->is_corpse() )
		return notify_fail("�����һ�㣬�ǲ��������\n");

	if( me->is_fighting(obj) )
		return notify_fail("���ͣ����ͣ����ͣ�\n");

	if( me->query_temp("hitting") )
		return notify_fail("���ͣ����ͣ����ͣ�\n");

	if (wiz_level(me) < wiz_level(obj))
		return notify_fail("�㲻��͵Ϯ��ʦ�ȼ�����ߵĶ��֡�\n");

	if (obj==me) return notify_fail("���Լ�������ô�벻����\n");

	if ( userp(me) && userp(obj) )
		return notify_fail("Ŀǰ��ֹpk��\n");

       if ( userp(me) && userp(obj) && obj->query("age") < 14 )
		return notify_fail("����ĳ�̫����, �����޸���֮�������Ҳ�µ����֡�\n");

/* add by cool for limit hit player to die */

	if ( userp(me) && userp(obj) && 
	   ( (obj->query("qi") < obj->query("max_qi")/2 ) 
	 || (obj->query("eff_qi") < obj->query("max_qi")/2 )) )
		return notify_fail("�Է��Ѿ��������������ٺ����д��ˡ�\n");

	if (!living(obj)) 
		return notify_fail(obj->name()+"�Ѿ��޷������ˣ�\n");
	if( userp(obj) ) {
		message_vision("\n$N����$n���һ����"+RANK_D->query_rude(obj)+"������һ�����ԣ�\n\n", me, obj);
		me->set_temp("hitting", 1);
		if (!me->is_busy()) me->start_busy(1);
		if (userp(me))
			obj->set_temp("other_kill/"+me->query("id"), 1);
		call_out("do_hit", 1, me, obj);
		return 1;
	}

	if( obj->query("can_speak") ) {
		message_vision("\n$N����$n���һ����"+RANK_D->query_rude(obj)+"���У�\n\n", me, obj);
		me->fight_ob(obj);
		if (obj->accept_fight(me)) obj->fight_ob(me);
		else obj->kill_ob(me);
	} else {
		message_vision("\n$N���һ������ʼ��$n����������\n\n", me, obj);
		me->fight_ob(obj);
		obj->kill_ob(me);
	}
/*
	if (obj && obj->query_temp("last_hit_by") == me && me->query_temp("hit_time") == time()) {
		if (me->add_temp("hit_count", 1) > 4) me->add("combat_exp", -1000);
		if (me->query("combat_exp") < 0) me->delete("combat_exp");
		log_file("punish", me->query("id") + " hit " + obj->query("id") + "�н��ˣ�\n");
	} else {
		me->set_temp("hit_time", time());
		me->delete_temp("hit_count");
	}
	if (obj) obj->set_temp("last_hit_by", me);
*/
	if (obj) COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
	return 1;
}

void do_hit(object me, object obj)
{
	if (!me) return;
	me->delete_temp("hitting");
	if (!obj) return;

	if(objectp(present(obj, environment(me)))) {
		if (userp(obj) && userp(me)
		&& (!living(obj) && me->query("mud_age") < (time() - me->query("birthday"))/24
		|| me->query("mud_age") / 6 > me->query("combat_exp"))) {
			message_vision("$N��Ȼ�����Լ��������ף���ʱ�����ҡ�\n", me);
			me->set("qi", -1);
		} else {

			COMBAT_D->do_attack(me, obj, me->query_temp("weapon"), 2);

			COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
		}
	}
}

int help(object me)
{
  write(@HELP
ָ���ʽ : hit <����>
 
���ָ��������һ������ֽ̡������ǡ��д����ա���������ʽ��ս��������
�㵽Ϊֹ�����ֻ����������������������ˣ����ǲ��������е� NPC ��ϲ��
��ܣ���������״����ı���Ҫ��ᱻ�ܾ���
 
�������ָ��: kill

PS. ����Է���Ը����������ս������Ȼ���������� kill ָ�ʼս������
    �� hit �� kill �������뿴 'help combat'.
HELP
    );
    return 1;
}
