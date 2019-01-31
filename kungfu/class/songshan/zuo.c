// Update by looklove at 2000/8/25
//Modify by Looklove for add log_file at 2000/9/1
// Last Modify by Looklove 2000/10/22 fixed fangqi's bug
// Modified by darken@SJ

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string do_ask();
string do_cancel();
string do_ask_hb();
string do_ask_grj();
string do_ask_times(object who);
string do_pay();

void create()
{
	object ob;
	
	set_name("������", ({ "zuo lengchan", "zuo", "lengchan" }));
	set("nickname", HIR"������������"NOR);
	set("long", "��ɽ�������������ǵ����������˲��������书��Ȼ�����뻯��
		Ϊ���ȸ����ǣ�����ٳ���������һ�ᵽ�������������֣��޲���Ȼ��\n");
	set("gender", "����");
	set("age", 52);
	set("per", 20);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 29);
	set("int", 28);
	set("con", 28);
	set("dex", 28);
	set("unique", 1);
	set("no_bark",1);
	
	set("max_qi", 4300);
	set("max_jing", 2800);
	set("eff_jingli", 3000);
	set("jiali", 50);
	set("combat_exp", 2800000);
	set("shen", -18000);
	set("max_neili", 8000);
	set("neili", 10000);

	set_skill("force", 290);
	set_skill("hanbing-zhenqi", 300);
	set_skill("dodge", 290);
	set_skill("zhongyuefeng", 290);
	set_skill("hand", 300);
	set_skill("songyang-shou", 300);
	set_skill("parry", 300);
	set_skill("sword", 290);
	set_skill("songshan-jian", 290);
	set_skill("literate", 200);
	map_skill("force", "hanbing-zhenqi");
	map_skill("dodge", "zhongyuefeng");
	map_skill("hand", "songyang-shou");
	map_skill("parry", "songshan-jian");
	map_skill("sword", "songshan-jian");
	prepare_skill("hand", "songyang-shou");
	set("inquiry", ([
//		"����": (: do_pay() :),
		"job": (: do_ask :),
		"����": (: do_ask :),
		"cancel": (: do_cancel :),
		"����": (: do_cancel :),
		"���": (: do_ask_hb :),
		"����": (:do_ask_times :),
		"����": (:do_ask_times :),
		"���ս�": (:do_ask_grj :),
	]));
	create_family("��ɽ��", 3, "������");
	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "sword.feiwu" :),
		(: perform_action, "hand.hanbing" :),
		(: exert_function, "juhan" :),
		(: exert_function, "hanbing" :),
	}));

	setup();
	if (clonep()) {		
		ob = unew(BINGQI_D("sword/guanri-jian"));	       
		if (!ob) ob = unew(BINGQI_D("gangjian"));
		ob->move(this_object());
		ob->wield();
		carry_object(ARMOR_D("changpao1"))->wear();
		carry_object(MEDICINE_D("tianwang"));
	}	   
	add_money("gold", 2);
}

void attempt_apprentice(object ob)
{
	if(ob->query_skill("hanbing-zhenqi",1) < 150 ||
	ob->query_skill("songshan-jian",1) < 150 ||
	ob->query_skill("songyang-shou",1) < 150){
		command("say ����书��������죬�ٻ�ȥ�����ɡ�");
		return;
	}
	if ((int)ob->query("songshan_points") < 300) {
		command("say ���Դ�������������͵��ˣ����������ҵ���������Ϊʦ��");
		return;}
 command("say �ã���������Щ������������Դ����书�������㻹�����");
	command("recruit " + ob->query("id"));
}

string do_cancel()
{
	object me;
	int exp;

	me = this_player();
	exp = me->query("combat_exp");
	
	if(!me->query_temp("quest") || me->query_temp("quest/family") != "��ɽ��")
		return "��û��������,��������ʲô?";
	
	me->clear_condition("job_busy");
	me->add("combat_exp",-(20+random(50)));
	if(exp > 500000){
	      me->add("combat_exp",-(10+random(40)));
	}
	me->apply_condition("job_busy",6+random(4));
	me->delete_temp("songshan_job");
	me->delete_temp("quest");
	return "��Ȼ��ɲ���Ҳû��ϵ,��ȥ�̿�������,�Ժ�����Ϊ���ǵĲ��ɴ�Ƴ���!";
}

string do_pay()
{
	object me = this_player();
	mapping fam;

	fam = me->query("family");
	if (!fam || fam["family_name"] !="��ɽ��")
	   return RANK_D->query_respect(me)+"��������ת�ɰɣ�BBB ���ǲ���׼��ġ�\n";
	if( me->query("ss/rec") )
	   return RANK_D->query_respect(me)+"����Ҫ���������һ��ֻ��Ҫһ�Ρ�\n";

	   me->set_skill("hand", me->query("max_pot") - 100);
	   me->set_skill("force", me->query("max_pot") - 100);
	   me->set_skill("sword", me->query("max_pot") - 100);
	   me->set("ss/rec", 1);

	return  "���ˣ���Ļ����ڹ����������ַ��Ҷ���������Ŀǰ���������ˣ�����ȥ�� hunthu �� darken �ˡ�\n" ;
}

string do_ask()
{
	object me, ob;      
	string type, t;
	mapping quest;
    
	me = this_player();
	ob = this_object();
    
	if(is_busy()) return "����æ���أ���ȵȡ�";
  
	if(me->query("combat_exp")>6000000)
		return "��Ĺ�����ô�ߣ������������ˡ�";

	if( me->query("combat_exp") < 100000 
	|| me->query("shen") > -1000)
		return RANK_D->query_respect(ob)+"�ҿ����ֽ�ɢ�����ж��ٻ����ټ��������������ܷ�������ȥ������أ�";
    
	if( me->query("job_name") == "��ɽ����")
		return "�ţ�����������˼�����ɴ�ƣ������š�";
 
	if( me->query_temp("quest/id")&& me->query_temp("songshan_job"))
		return "��������ȥ"+me->query_temp("quest/type")+me->query_temp("quest/name")+"������ô�������";
       
	if( me->query_condition("job_busy"))
		return "�ţ�������æ�������š�"; 
     
	type = random(2)?"��":"ɱ";

	// get a random npc from TASK_D.
	if(!mapp(quest= TASK_D->get_quest(me, 0, type, "��ɽ��"))) 
		return "�ţ�����������˼�����ɴ�ƣ������š�"; 
	    
	me->set_temp("quest", quest);
	me->apply_condition("job_busy", 25+random(30));    
	t = TASK_D->get_time(quest["time"]);   // get time limit.
    
	me->set_temp("songshan_job", 1);
	me->set("job_name", "��ɽ����");
	if(type == "ɱ"){
	    command("grin");
	    command("say �������ˣ��е��ӻر�"+quest["name"]+"���˶�����������֮�����������ô������");
	    return "�ٺ٣�����"+quest["place"]+CYN"һ������ȥ����ɱ�ˣ������"+t+CYN"֮ǰ��������ʬ��ϻ�����\n";
	}
	else{
	    command("nod");
	    command("say ���ˣ�"+quest["name"]+"���ҽ��鲻���������������������֮�¼�ֱ���練�ơ�");
	    return "��ʹ�����ȥ"+quest["place"]+CYN"�������������"+t+CYN"֮ǰ�ϻ�����\n";    
	}   
}

int accept_object(object who, object ob,object me)
{
       int type,count,exp,pot;
       me=this_object();
       
       // check job.
       
       if( who->query_temp("quest/family") != "��ɽ��")
		    return 0;
			
       type = TASK_D->is_target(ob, who);
       switch (type){
	    case 0: command("say ���ø�"+ob->name()+"���Ҹ��");
		    return 0;
	    case -1:command("say Ү���������㲻ȥ����ɱ�˶���ȥ�ˣ�������");
		    return 0;
	    case -2:command("say �ٺ٣�˭����ȥ��ɱ���ˣ���ֱ�Ǹ�����ɽ��Ĩ�ڣ�");
		    who->apply_condition("job_busy", 40);
		    return 0;
	    case -3:command("say �ţ���ô�òŰ��꣬���ʲôȥ�ˣ����ҹ�һ��ȥ��");
		    who->apply_condition("job_busy", 30);
		    return 0;
	    case -4:command("say Ŷ�����Ǹ�ͬ��ͬ�Ե��ˣ�������ù�ɣ�");
		    return 0;
	    default:command("haha");
		    command("say �ã��ã�����²����ǿ�����ӡ�");
		    message_vision("\n$N��$n����һЩ��ѧ�ϵ����ѣ�$n������˼�ص���ͷ��\n",me, who);
		    // give rewards.
		    TASK_D->give_reward(who, who->query_temp("quest"), -1);
	
	who->add("songshan_points", 1);
	who->apply_condition("job_busy",2+random(5));
	who->delete_temp("songshan_job");
	
	count = who->query("songshan_points");
	if (count<1) count=1;
	pot= who->query_temp("quest/pot_reward");
	exp= who->query_temp("quest/exp_reward");
	who->delete_temp("quest");

	log_file( "job/ss_job",sprintf("%s %s(%s)��%d����ɽɱ��������%d�㾭�飬%d��Ǳ�ܣ����飺%d\n",
	ctime(time())[4..19],who->name(),who->query("id"),count,exp,pot,who->query("combat_exp")));
		    
	who->add("songshan_points", 1);
	call_out("destroy", 1, ob);
	return 1;
	    }
      return 1;
}

void destroy(object ob)
{
	destruct(ob);
}

void init()
{       
	object ob;
	ob = this_player();

	::init();
	ob->delete_skill("hanbing-shenzhang");
	ob->delete_skill("songyang-bian");
	ob->delete_skill("songyang-zhang");
	if( interactive(ob = this_player()) && !is_fighting() && !is_busy()
	   && ob->query_temp("quest/family") == "��ɽ��"
	   && ob->query_temp("quest/type") == "��") {
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
}

void greeting(object me)
{
	object target, ob;
	mapping quest;
	
	if( !me || environment(me) != environment() || !living(me)) return;
	
	if (!mapp(quest = me->query_temp("quest")) || quest["type"] != "��"
	|| !stringp(quest["id"])) return;
	
	command("nod "+me->query("id"));
	
	ob = this_object();
	
	if(objectp(target=present(quest["id"], environment(me)))
	  && target->query_temp("songshan_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"����������ɽ���ֶ���һ����������������");
		/*
		if ( quest["time"] < time()) {
			command("say �ţ�"+me->name()+CYN"����ô�òŰ��꣬���ʲôȥ�ˣ����ҹ�һ��ȥ��");
			me->delete_temp("quest");
			me->set_temp("quest/last_id", quest["last_id"]);
			me->apply_condition("job_busy", 30);
			call_out("done", 3, target, me, quest, -1);
		}
		
		else */
		call_out("done", 3, target, me, quest, 1);
		return;
	}
}

void done(object target, object me, mapping quest, int i)
{    
       int count,exp,pot;

       if(me && i >= 0){
       if(target){	  
	    message_vision("\n$N��ͷ����"+me->name()+"�����޲���������ָ�������У��͵��ǳ����ļ�����ɣ�\n", target, me);
	    tell_room( environment(me), target->name() + "��" + me->name()+ "����С����˵��Щ����\n", ({ me, target }) );
	    // give rewards.
	    TASK_D->give_reward(me, me->query_temp("quest"), -1, ABS(me->query("songshan_points")/100));
	    me->apply_condition("job_busy",2+random(5));
	if ( me->query("family/family_name") == "��ɽ��"
	  && me->query_skill("hanbing-zhenqi"))
	    me->improve_skill("hanbing-zhenqi",me->query("int")*2);

	count = me->query("songshan_points");
	if (count<1) count=1;
	pot= me->query_temp("quest/pot_reward");
	exp= me->query_temp("quest/exp_reward");
	log_file( "job/ss_job",sprintf("%s %s(%s)��%d����ɽ����������%d�㾭�飬%d��Ǳ�ܣ����飺%d\n",
	ctime(time())[4..19],me->name(),me->query("id"),count,exp,pot,me->query("combat_exp")));
	me->delete_temp("quest");
	me->delete_temp("songshan_job");
	me->add("songshan_points", 1);
	tell_room(environment(target), target->query("name")+"��Ц��������֪�͵��Ӵ����µ��᷿��Ϣȥ�ˡ�\n", ({target}));
	if(target->return_home()){
		target->delete_temp("songshan_job");
		target->delete_temp("last_lost_to");
		target->clear_condition("songshan_busy");
		target->set("chat_chance", target->query("chat_c"));
		if(!target->query_temp("location"))
			target->delete("location");
		target->set_leader(0);
		target->reincarnate();
	}
	else destruct(target);
		}
	}
	else if(target){ 
		tell_room(environment(target), target->query("name")+"��Ц��������֪�͵��Ӵ����µ��᷿��Ϣȥ�ˡ�\n", ({target}));   
		destruct(target);
	}
}

string do_ask_hb()
{
	object me = this_player();

	if (!me->query("ss/hb_improve"))
		return "ʲô����Ǹ���ѽ����";
	if (random(2)==1)
		return "��������ص���Ҳ���Ǻ������";
	me->set_temp("ss/hb_1",1);
		return "��ŵص����һ��Ͽ�ȸ���������ص���ʵ���벻�����ˡ�";
}

string do_ask_grj()
{
	object me=this_player() , weapon;
	
	if ((string)me->query("family/master_name") != "������")
		return 0;	
	weapon = present("guanri jian", this_object());
	if(!objectp(weapon))    weapon = unew(BINGQI_D("sword/guanri-jian"));
	if(!objectp(weapon))
		return "���ս��Ѿ�����ʦ��������,���ڲ��������";  
	command("unwield guanri jian");
	weapon->move(me);
	command("wield jian");
	message_vision("\n$N����$nһ�ѹ��ս���\n", this_object(), me);
}


 string do_ask_times(object who)
{	  
	object me;
	int i;
	me = this_player(); 
	if(!intp(i = me->query("songshan_points")))
		return "�����С�쵰����������ˣ�����ɱ����? ��ƭ�� ?"; 
	message_vision("$N����$n�����룬˵������Ŀǰ�Ѽǹ�" + chinese_number(i) + "�Ρ�\n", who,me);
	return "����ɽ�����ͷ�����������Ŭ���ɣ�";
}

