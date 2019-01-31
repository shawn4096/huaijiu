// guard.c
// by snowman@SJ 11/03/2000
// Add log By Looklove@SJ 2000,11,23
// Modify By Looklove 2001,1,11

#include <ansi.h>

inherit F_CLEAN_UP;
int help(object);

int main(object me, string arg)
{
	object obj, *enemy;
	string callname, msg;
	int i;
	
	if( !arg )
		return help(me);

	if(environment(me)->query("no_fight")) 
	       return notify_fail("���ﲻ��ս����\n");

	if(!objectp(obj = present(arg, environment(me))) 
	|| !userp(obj)
	|| obj->is_corpse() 
	|| obj->is_ghost() )
		return 0;
	
	if (me->is_busy()) return notify_fail("����æ���ء�\n");

	if( obj == me ){ 
		message_vision("$N���˸����ͣ�һ��������ߵ���̬��\n", me);
		write("������Լ�������˧���ˡ�\n");
		return 1;
	}

	if (!obj->is_fighting() ){
		write("����û��ս�����ء�\n");
		return 1;
	}
	if( obj->is_killing(me->query("id")) || me->is_killing(obj->query("id"))){
		write("�������ں��������಩���㻹�пձ�������\n");
		return 1;

	}
	if( me->is_fighting() ){
		write("������û��أ���æ�������˵�ɣ�\n");
		return 1;
	}
	
	enemy = obj->query_enemy();
	i = sizeof(enemy);
	while (i--) {
		if (enemy[i]->is_killing(obj->query("id"))) break;
		if (obj->is_killing(enemy[i]->query("id"))) break;
	}
	if (i < 0) {
		write(obj->name()+"�ͱ������д��أ�����¡�\n");
		return 1;
	}
	
	if(userp(obj) && obj->query_condition("killer") && !me->query_condition("killer")){
		write("����ɱ�˷���С�ı�ͨ����\n");
		return 1;
	}
	
	if( me->query("combat_exp") < obj->query("combat_exp") / 3 ){
		write("��ӴӴ������㱾�£����Ǳ�ȥ���ְ��ŵİɣ�\n");
		return 1;
	}

	if( obj->query("env/no_protect") || obj->query("env/no_guard") ){
		msg = CYN"$N��Ҫ����ǰȥ��$n��\n";
		if( stringp(callname = obj->query("env/no_protect")) )
			msg += "����$n����$Nһ�ɣ�"+callname+"��\n"NOR;
		else msg += "��������$n������õ�$N�İ�����\n"NOR;
		message_vision(msg, me, obj);
		return 1;
	}
	
	callname = RANK_D->query_respect(obj);
	me->start_busy(1);

	if(me->query("race")=="����"){
		if(me->query("mute") || obj->query("race")!="����")
			msg = "\n$NͻȻ��ǰ��������$n��ǰ����������Ҫ����$p��\n\n";
			
		else if(stringp(me->query("env/protect_msg")) && strlen(me->query("env/protect_msg")) < 50 )
			msg = "\n$Nһ���Ӻ�����$n��ǰ���������"+me->query("env/protect_msg")+"����\n\n";
			
		else if(me->query("combat_exp") > obj->query("combat_exp")*2){
			if(me->query("shen") < -10000)
				msg = "\n$Nһ������$n����"+RANK_D->query_rude(obj)+"��ú�ѧ�ŵ㣬����"+RANK_D->query_self_rude(me)+"����ô�����˵ģ�����\n\n";
			else    msg = "\n$Nһ�´�����$n��ǰ����"+callname+"���ÿ�����"+RANK_D->query_self(me)+"��������񫣬����һ�߿��Űɣ�����\n\n";
		}
		
		else if(obj->query("combat_exp") > me->query("combat_exp")*2){
			if(me->query("shen") < -10000)
				msg = "\n$N��$n��ǰһվ����"+callname+"������һ�Կ��ţ�����"+RANK_D->query_self_rude(me)+"��Ҫ�������˻�ˮ������\n\n";
			else    msg = "\n$N��ɫ���أ�����$n��ǰ����"+callname+"���ÿ����ҵ�Ҫ������ʲô�˸Ҵ�������⣡��\n\n";
		}
		
		else {
			if(me->query("shen") < -10000)
				msg = "\n$Nһ��Ծ��$n��ǰ����"+callname+"������������"+RANK_D->query_self_rude(me)+"����ˣˣ����ЪЪ������\n\n";
			else    msg = "\n$N����$n���ظ��ĵ������죺����"+RANK_D->query_self(me)+"�ڣ�ʲô�˶����ܴ����Ƕ����˺�ȥ����\n\n";
		}
		
	}
	
	else msg = "\n$N���һ������Ȼ����$n��ǰ��������Ҫ����$p����\n\n";
	
	message_vision(CYN+msg+NOR, me, obj);

	if(userp(obj))
		tell_object(obj, HIC "��" + me->name()+ "(" + me->parse_command_id_list()[0]+ ")һ������������ǰ����ס����󲿷ֵĶ��֣�\n" NOR);
	
	enemy = obj->query_enemy();
	
	for(i = 0; i < sizeof(enemy); i++){
		if(!enemy[i]) continue;
		if(!living(enemy[i])) continue;
		if(enemy[i]->query("no_ansuan")) continue;
		if (obj->is_killing(enemy[i]->query("id")) && !enemy[i]->is_killing(obj->query("id"))) continue;
		enemy[i]->remove_enemy(obj);
		obj->remove_killer(enemy[i]);
		me->fight_ob(enemy[i]);
		enemy[i]->fight_ob(me);
		
		if (!enemy[i]->is_killing(obj->query("id")) 
		&& random(enemy[i]->query("combat_exp")) > random(me->query("combat_exp")/2))
			enemy[i]->kill_ob(me);
/*
		if (userp(obj))
		log_file("static/guard",sprintf("%s(%s) guard %s(%s) with %s(%s) at %s.\n",
		me->name(),me->query("id"), obj->name(), obj->query("id"),enemy[i]->name(),enemy[i]->query("id"),ctime(time()) ) );
*/
	}       
	return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : guard <����>
 
���ָ�����㱣��һ��ս���е����
�����ºʹ�����ս��������������ڶԷ���η�Ӧ���Ϳ���ʱ������ˡ�

�������ָ��: fight��kill��hit��ansuan

HELP);
    return 1;
}

