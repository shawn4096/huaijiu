#include <ansi.h>

string gb_job1()
{
	object me = this_player();
	
	if(me->query_temp("gb_job1"))
	    return "���ϴε�����û����ɣ�����ô������������¡�";
	command("say �ղ��ҽӵ���������״��ɸ봫�飬���Ĺ�����\n"
	+   "���ʮ�������Ҵ��Σ�ǰ���ѳ����ס�" );
	new(__DIR__"obj/gaoji-wenshu")->move(me); 
	message_vision("$N��$nһ�Ÿ漱���顣\n", this_object(), me);
	me->set_temp("gb_job1",1);
	return "���ٽ���ݸ漱���齻���߹��ؽ����������������������";
}

string gb_job2()
{
	object me = this_player(), ob = this_object();
	mixed *ob_list;
	int max,i;
	object obj1;
	
	if( me->query_temp("gb_job2") )
	     return "�㲻���Ѿ��ӹ���������";
		
	ob_list = filter_array(children(USER_OB), (: clonep($1) && !wizardp($1) :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
	   obj1 = ob_list[i];
	   if (obj1->query_temp("gb_job2") )
	    return "����������Ѿ�����" + obj1->query("name")
		+"("+capitalize(obj1->query("id"))+")"+"ȥ���ˡ�";
	} 

	if( ob->query_temp("gb_job2") )
	    return "����������û��ʲô������Ը��㡣";
		
	this_object()->set_temp("gb_job2",1);
	me->set_temp("gb_job2",1);
	me->set("job_name","���ղ��ϳ�");
	me->apply_condition("gb_job2",40);
	me->apply_condition("job_busy", 10);

	command("say �ɹŴ�����Ҵ��������ǣ�ÿ�ζ�������Ϊ����֮����\n"
	    +   "�����������������͵Ϯ�������ؽ��������ܶ�ʧ�ܡ�");
	return  "ǰ���챾����Ӵ�̽�������Ǳ���һ�����£������վ���\n"
	    +   "�ɹű����ؿ��顣��Ӹô�����ȥ���Ż��յ��ɹ����֣�\n"
	    +   "�Խ�������֮Χ��";
}

string gb_job3()
{
	object me = this_player(), ob = this_object();
	mixed *ob_list;
	int max,i;
	object obj1;
	
	if( me->query_temp("gb_job3") )
	      return "�㲻���Ѿ��ӹ���������";

	if( me->query("job_name") == "��ɱ��Ԫ˧") 
	      return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";

	if(me->query_condition("job_busy"))
	      return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";
			    
	ob_list = filter_array(children(USER_OB), (: clonep($1) && !wizardp($1) :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
	    obj1 = ob_list[i];
	    if (obj1->query_temp("gb_job3") )
		return "����������Ѿ�����" + obj1->query("name")
		+"("+capitalize(obj1->query("id"))+")"+"ȥ���ˡ�";
	}

	if( ob->query_temp("gb_job3") )
		return "����������û��ʲô������Ը��㡣";
			
	command("say �ɹŴ��ɸ����ճ�����ʾ�����ʮ�򣬱�����·����ͼ\n"
	    +   "������������������һϦ������Ϊ��֮�ƣ�ֻ��Ѱ����ɱ\n"
	    +   "�ɹŴ󽫣�������ʹ�ɹŴ����Χ������\n" );
	
	this_object()->sset_temp("gb_job3",1);
	me->set_temp("gb_job3",1);
	me->apply_condition("gb_job3", 50);
	me->apply_condition("job_busy", 10);
	me->set("job_name","��ɱ��Ԫ˧");
	return  "��ؤ������״���Ѿ�Ǳ���ɹž��У����ȥ�������ŵ�����\n"
	    +   "�����������ɹŴ�Ӫ���Ż���ɱ�ɹŴ󺺡�";
}

string gb_job4()
{
	object me = this_player(), ob = this_object();
	int max,i;
	object obj1;
	object *ob_list;
	object ob2;
	
	if( me->query_temp("gb_job4") )
	      return "�㲻���Ѿ��ӹ���������";
		
	if(me->query_condition("job_busy") || me->query_condition("gb_job_busy"))
	      return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";

	if( me->query("job_name") == "������Ħ��") 
	      return "���ϴ����������ˣ���������Ϣһ����˵�ɡ�";
	    
	ob_list = filter_array(children(USER_OB), (: clonep($1) && !wizardp($1) :));
	max=sizeof(ob_list);
	for (i=0;i<max;i++){
	    obj1 = ob_list[i];
	    if (obj1->query_temp("gb_job4") )
	    return "����������Ѿ�����" + obj1->query("name")
		+"("+capitalize(obj1->query("id"))+")"+"ȥ���ˡ�";
	}

       if( ob->query_temp("gb_job4") )
	    return "����������û��ʲô������Ը��㡣";
			
       ob2 = new("/clone/npc/zhong-shentong");
       if( ob2 ){
//       if( ob2->query("winner") == me->query("id"))
//	   return "�����ǵ���������������������Ҳ�ǲ�����¡�\n";
	 destruct(ob2);
       }
    
       command("say �ҸղŽӵ���������״��ɸ봫�飬����һƷ��\n"
	   +   "��ǲ�������ֶ�������ͼ��ɱ�ξ���˧�����\n" );
	
       this_object()->sset_temp("gb_job4",1);
       me->set_temp("gb_job4/asked",1);
       me->apply_condition("gb_job4",30);
       me->apply_condition("job_busy", 30);
       me->set("job_name", "������Ħ��");     
       return  "��Ħ����������ʿ�����ıؾ�֮�أ����ٴ�����������\n"
	   +   "���������ɱ��������ʿ�в������֣��������ӣ���\n" 
	   +   "���󷨣��Բ���ȫ���м��мǡ�";
}
