// Write by look
// Modify by bbb
// Modify by snowman@SJ 17/02/2000
// check leitaiuser.

#include <ansi.h>
#include <login.h>
#define SYNTAX  "ָ���ʽ��catch <ĳ��> because <ԭ��>\n"

inherit F_CLEAN_UP;

int main(object me, string str)
{
	object ob, where;
	int times, t;
	string name, reason;
 
	if(!str || sscanf(str, "%s because %s", name, reason)!=2 )
		  return notify_fail(SYNTAX);
	       
	if (!objectp(ob = LOGIN_D->find_body(name))) 
		  return notify_fail("���...���... ���������?\n");
	
/*
	if (wiz_level(ob))
		  return notify_fail("�Է��ǹ�ͬ�ܶ���ս���ޣ�����������̫�ðɣ�\n");
*/

	if(!objectp(where = environment(ob)))
		  return notify_fail("����˲�֪����������Ү... :-( \n");
	
	if (ob->query("registered") < 2)
		return notify_fail("����˲�����ʽע�����ҡ�\n");

	if (file_name(where) == RELAX_ROOM) 
		  return notify_fail("���Ѿ����һ�Դ˼���ˣ�������ץ�ˡ�\n");
	
	if (base_name(ob) == "/cmds/leitai/leitaiuser")
		return notify_fail(ob->name() + "�����Ǳ�����̨Clone�����ģ�����̨�������뿪�����ˡ�\n");
		
	tell_room(where, MAG"�����Ʈ����λ��ò��Ů������"+ob->query("name")+MAG"�ڿն�ȥ�ˡ�\n"NOR, ({ ob }));
	tell_object(ob, MAG"��λ��ò��Ů����������ǰ�������㻺��Ʈ������....\n"NOR);
	
	times = ob->add("rules", 1);
	if (times < 6) t = 6;
	else t = times;
	tell_object(ob,"����Ϊ��" + reason + "�ݣ�Υ���齣��Ϸ���򹲼�" + CHINESE_D->chinese_number(times) + "�Σ�
	      ��������ؽ������һ�Դ" + CHINESE_D->chinese_number(t*10) + "���ӵĴ�����\n");

	message("shout", HIC "\n�����ɡ�"+ob->query("name")
		+"("+capitalize(ob->query("id"))
		+")��Ϊ��" + reason + "�ݣ�Υ���齣��Ϸ���򹲼�" + CHINESE_D->chinese_number(times)+ "�Σ���������ؽ���"
		+CHINESE_D->chinese_number(t*10)+"���ӵĴ�����\n\n" NOR, users());

/*
	if (times > 3){
		int t = times > 50? 50: times;
		tell_object(ob,"ͬʱ��ȥ�㾭��ֵ�İٷ�֮"+CHINESE_D->chinese_number(t)+"��Ϊ������\n\n");
		message("channel:chat", HIC "�����ɡ�ͬʱ��ȥ����ֵ�İٷ�֮"+CHINESE_D->chinese_number(t)+"��Ϊ������\n\n" NOR, users());
		ob->add("combat_exp",-ob->query("combat_exp")/100*t);
	}
*/
	
	ob->apply_condition("relax", t*30);
	ob->move("/d/wizard/relax");
	ob->set("relax_timeout_room", file_name(where));
	
	tell_object(me, "���"+(string)ob->query("name")+"ץ�����һ�Դ��\n");
	tell_room(environment(ob), MAG"��λ��Ů����"+ob->name()+MAG"Ʈ������"+ob->name()+MAG"����������\n"NOR, ({ ob }));

	ob->set("startroom", RELAX_ROOM);

	log_file("static/CATCH", sprintf("[%s] %s ��Ϊ [%s] �� %s(%s) ץ���һ�Դ������Υ�� %d �Ρ�\n",
		ctime(time())[0..15], name, reason, (string)me->query("name"),me->query("id"), times));
	    
	
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : catch <ĳ��> because <ԭ��>

��ָ������㽫ĳ��Υ�������������͵��һ�Դ��
����ʱ�䵽���Զ��ͷš�
��������Զ��ۼӡ�
HELP
    );
    return 1;
}

