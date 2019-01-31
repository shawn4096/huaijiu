// kill.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj;
	string callname, msg;

	if (!arg)
		return notify_fail("����ɱ˭��\n");

	if(!objectp(obj = present(arg, environment(me))))
		return notify_fail("����û������ˡ�\n");

	if( environment(me)->query("no_fight") && !obj->query_condition("killer"))
		return notify_fail("���ﲻ׼ս����\n");

	if (userp(obj) && me->query("no_pk"))
		return notify_fail("���Ѿ�����ϴ�֣����ǲ�Ҫ���뽭�������ɣ�\n");

	if (userp(me) && obj->query("no_pk") && !obj->query_condition("killer"))
		return notify_fail(obj->name()+"�Ѿ�����ϴ�֣����ǲ�Ҫ���뽭�������ɣ�\n");

	if (userp(obj) && me->query("ת��id")) // add by Looklove for share id
	return notify_fail(HIR"���id���ڽ��ֱ��˵�id��δcutת��ʱ��exp����ɱ��������ң�\n"NOR);

	if (strsrch(file_name(environment(me)),"/d/wuguan/") >= 0 && !obj->query_condition("killer"))
		return notify_fail("����ڽ�ֹɱ�ˡ�\n");

	if (!obj->is_character() || obj->is_corpse())
		return notify_fail("�����һ�㣬�ǲ����ǻ��\n");

	if (wiz_level(me) < wiz_level(obj))
		return notify_fail("�㲻�ܹ�����ʦ�ȼ�����ߵĶ��֡�\n");

	if (obj == me) return notify_fail("�� suicide -f ָ���ȽϿ�Щ��\n");

	if (userp(obj) && me->query_condition("killer") > 180)
		return notify_fail("һ�ղ���������ɱ����ˡ�\n");

       if ( userp(me) && userp(obj) && strsrch(file_name(environment(me)),"/cmds/leitai/bwdh/") == -1 && !(int)obj->query_condition("killer") && me->query("combat_exp") < 3000000 && obj->query("combat_exp") < 3000000)
		return notify_fail("�㲻������������,�޷��˺��Է���\n");

	if (me->is_killing(obj->query("id")) && me->is_fighting(obj))
		return notify_fail("���ͣ����ͣ�\n");

	if (me->query_temp("combat_yield"))
		return notify_fail("�����򲻻����أ���ôɱ��\n");

	callname = RANK_D->query_rude(obj);

	if(me->query("race")=="����"){
		if(me->query("mute"))
			msg = "\n$NͻȻ����$n��˫��ͨ�죬������Ҫ��$p�����أ���\n\n";
			
		else if(stringp(me->query("env/kill_msg")) && strlen(me->query("env/kill_msg")) < 50 )
			msg = "\n$N����$n���һ������"+callname+"��"+me->query("env/kill_msg")+"����\n\n";
			
		else if(me->query("combat_exp") > obj->query("combat_exp")*2){
			if(me->query("shen") < -10000)
				msg = "\n$N����$n����һ�ڣ���"+callname+"������������ʱ��"+RANK_D->query_self_rude(me)+"���쿴�㼫��˳�ۣ������ɣ�����\n\n";
			else msg = "\n$N����$n�������"+callname+"����Ǻ�"+RANK_D->query_self_rude(me)+"�����֣�������˾ȥ����һ״�ɣ�����\n\n";
		}
		
		else if(obj->query("combat_exp") > me->query("combat_exp")*2){
			if(me->query("shen") < -10000)
				msg = "\n$N����$nһ����Ц����"+callname+"������ƽʱҫ������������"+RANK_D->query_self_rude(me)+"��Ҫȡ������������\n\n";
			else msg = "\n$N����$n�ٺ�һЦ��"+callname+"�����似�����㣬���������ƴ����ҲҪ������ʬ��ϣ���\n\n";
		}
		
		else {
			if(me->query("shen") < -10000)
				msg = "\n$N����$n�ͺ�һ������"+callname+"������Ľ��������ļ��գ���"+RANK_D->query_self_rude(me)+"������·�ɣ�����\n\n";
			else    msg = "\n$N����$n�ȵ�����" + callname + "���������ѵ����������"+RANK_D->query_self_rude(me)+"����������ɣ���\n\n";
		}
		
	}
	else msg = "\n$N���һ������Ȼ����$n��������Ҫ��$pɱ������\n\n";

	message_vision(msg, me, obj);

	me->delete_temp("guarding");
	obj->set_temp("guarding", 1);
	me->kill_ob(obj);
//add by cool for have a pk logs

	if (userp(me) && userp(obj))
		log_file("ATTEMP_KILL",sprintf("%s(%s) ��ͼɱ�� %s(%s) on %s\n",
		me->name(1),me->query("id"),obj->name(1),obj->query("id"),ctime(time())));

	if (!userp(obj))
		obj->kill_ob(me);
	else if (!me->is_killing(obj->query("id"))) {
		if (userp(me))
			tell_object(obj,
				HIR  + me->name()+ "("
				+capitalize(me->parse_command_id_list()[0])+")����������ಫ��������������������嶯��\n"NOR
			);
	} else {
		obj->fight_ob(me);
		if (userp(me)) {
			tell_object(obj, HIR "�����Ҫ��" + me->name()+ "("
				+capitalize(me->parse_command_id_list()[0])+")�����ಫ������Ҳ���������һ�� kill ָ�\n"NOR
			);
			if (!obj->query_condition("killer")) {
                                if (!obj->query_temp("kill_other/"+me->query("id")) && !me->query_temp("other_kill/"+obj->query("id"))) {
        	                          me->add_busy(2);
	                                  message_vision("$N�޷�������$n����������\n", me, obj);
                                }
                        }
		}
	}

	if (obj && me && userp(obj) && userp(me)
	&& (!living(obj) && me->query("mud_age") < (time() - me->query("birthday"))/24
	|| me->query("mud_age") / 6 > me->query("combat_exp"))) {
		message_vision("$N��Ȼ�����Լ��������ף���ʱ�����ҡ�\n", me);
		me->set("qi", -1);
	}

	return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : kill <����>
 
���ָ������������ʼ����һ�����������ͼɱ���Է���kill �� fight ����
��ͬ����˫�������浶ʵǹ�ش򶷣�Ҳ����˵����������ˡ����� kill ֻ�赥��
��һ����Ը�Ϳ��Գ������������κ���ʹ�� kill ָ��Ὺʼս����ͨ�����
�Է��� NPC �Ļ�������Ҳ��ͬ������ʹ�� kill��

�����˶���ʹ�� kill ָ��ʱ����ֺ�ɫ�����������㣬����һ����Ҷ��ԣ����
��û�ж�һ������ʹ�ù� kill ָ��Ͳ��Ὣ�Է���Ĵ��˻�ɱ��( ʹ�÷�����
��)��

�������ָ��: fight


�й� fight �� kill �������뿴 'help combat'.
HELP
    );
    return 1;
}
