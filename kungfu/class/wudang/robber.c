// Modify By River@SJ
#define NAME_D	  "/inherit/misc/r_name"

inherit NPC;
inherit F_UNIQUE;
inherit F_SAVE;
#include <ansi.h>

int do_kill(object me);

string *sword_skill = ({ 
"taiji-jian","xuantie-jianfa","fumo-jian","jinshe-jianfa","qingmang-jian","yuxiao-jian",
"yunu-jianfa","songshan-jian","murong-jianfa","huashan-jianfa", "duanjia-jianfa",
"huifeng-jian","liangyi-jian","quanzhen-jianfa" }); 

string *blade_skill = ({ 
"cibei-dao","fanliangyi-dao","liuhe-daofa","murong-daofa","qingmang-jian","wenjia-daofa", 
"shandian-daofa","xiuluo-dao","xuanxu-daofa", "yanxing-daofa",}); 

string *staff_skill = ({ "wuchang-zhang","fengmo-zhang","xinyuegong" }); 

string *club_skill = ({ "weituo-chu","zui-gun","weituo-gun","xinyuegong" }); 

string *whip_skill = ({ "piaomiao-bianfa","riyue-bian" }); 

string *dodge_skill = ({ 
"shuishangpiao","suibo-zhuliu","yanling-shenfa","yufeng-xiang","tianlong-xiang",
"yunu-shenfa","zhaixingshu","xiaoyaoyou","zhongyuefeng","huashan-shenfa","tiyunzong" }); 

string *weapon_list = ({ "chui","sword","blade","whip","gun","sword","gangzhang","blade" }); 

string *first_title = ({"����","����","����","��ԭ","����","����","�ӱ�","����"});
string *second_title = ({ "�ݿ�","կ��","���","ɽ��","����","����", "����"});

void create()
{
	string s_sword,s_blade,s_club,s_whip,s_staff,s_dodge, weapon,title;
	mapping name;
	int i;
	
	i = random(3) + 1;

	name = NAME_D->get_random_name(i);
	title = first_title[random(sizeof(first_title))]; 
	title += second_title[random(sizeof(second_title))];
	s_sword = sword_skill[random(sizeof(sword_skill))];
	s_blade = blade_skill[random(sizeof(blade_skill))];
	s_club  = club_skill[random(sizeof(club_skill))];
	s_whip  = whip_skill[random(sizeof(whip_skill))];
	s_staff = staff_skill[random(sizeof(staff_skill))];
	s_dodge = dodge_skill[random(sizeof(dodge_skill))];
	weapon = weapon_list[random(sizeof(weapon_list))];

	set_name(name["name"], name["id"]);
	set("title", HIW+title+NOR);
	set("gender", (i==0?"Ů��":"����"));
	set("age", 20 + random(40));
	set("long", "��һ�һ�������ɷ��ģ����ʱ��ʱ����а�����Ц��\n");
	set("combat_exp", 8000000);
	set("meitude", "peaceful");
	set("str", 25);
	set("dex", 30);
	set("int", 30);
	set("con", 30);
	set("max_qi", 20000);
	set("max_jing", 20000);
	set("max_neili", 5000);
	set("neili", 5000);

	set_skill("huagu-mianzhang", 500);
	set_skill("strike", 500);
	set_skill("xinyuegong", 500);
	set_skill("taiji-shengong", 200);
	set_skill("sword", 500);
	set_skill("dodge", 500);
	set_skill("cuff", 500);
	set_skill("force", 500);
	set_skill("parry", 500);
	set_skill("blade", 500);
	set_skill("hammer", 500);
	set_skill("club", 500);
	set_skill("staff", 500);
	set_skill("whip", 500);
	set_skill("literate",500);
	set_skill(s_sword, 500);
	set_skill(s_blade, 500);
	set_skill(s_club, 500);
	set_skill(s_whip, 500);
	set_skill(s_staff, 500);
	set_skill(s_dodge, 500);
	map_skill("force", "taiji-shengong");
	map_skill("sword", s_sword);
	map_skill("dodge", s_dodge);
	map_skill("parry", "taizuquan");
	map_skill("hammer", "xinyuegong");
	map_skill("blade", s_blade);
	map_skill("club", s_club);
	map_skill("whip", s_whip);
	map_skill("staff", s_staff);
	map_skill("strike", "huagu-mianzhang");
	prepare_skill("strike", "huagu-mianzhang");
	prepare_skill("cuff", "taizuquan");
	setup();
	carry_object(BINGQI_D(weapon))->wield();
	carry_object(ARMOR_D("yexing-yi"))->wear();
	add_money("gold", random(4)+2);
	set("chat_chance", 5);
	set("chat_msg", ({
		(: random_move :)
	}) );
	if (clonep())
		call_out("dest", 800);
}

void init()
{
	object ob;       

	::init();
	if( interactive(ob = this_player())){
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
}

void greeting(object ob)
{
	object me = this_object();
	
	if (!ob 
	 || !present(ob) 
	 || me->query_temp("target") != ob->query("id"))
		return;

	if (ob->query("wd/wd_job")){
		ob->add_busy(1);
		me->start_busy(1);
		remove_call_out("checking");
		call_out("checking", 1, me, ob);
		remove_call_out("dest");
		call_out("dest",300);
		remove_call_out("do_kill");
		call_out("do_kill", 0, ob);
	}
}

int do_kill(object ob)
{
	mapping skills;
	string *sk;
	object me; 
	int lv,exp,i,b_exp,p;

	me = this_object();
	lv = (int)ob->query("max_pot");
	lv = lv-100;
	exp = ob->query("combat_exp");
	b_exp = 300000;
	p = random(2)+1;
	
	if(!ob) return 0;
	ob->set("wd/wd_bonus", p);	
	if (exp < 500000){
	     me->set("combat_exp",exp);
	     lv = lv *(p+6)/9;
	}
	else {
	     me->set("combat_exp",(exp+random(50000*(exp/b_exp)*p)));
	     lv = lv *(p+8)/9;
	}     
	me->set("qi",(int)ob->query("max_qi")*5/4);
	me->set("max_qi", (int)ob->query("max_qi")*5/4);
	me->set("eff_qi", (int)ob->query("max_qi")*5/4);
	me->set("jing",(int)ob->query("max_jing"));
	me->set("max_jing",(int)ob->query("max_jing"));
	me->set("eff_jing",(int)ob->query("max_jing"));
	me->set("neili",(int)ob->query("max_neili")*5/4);
	me->set("max_neili",(int)ob->query("max_neili"));
	me->set("jingli",(int)ob->query("max_jingli"));
	me->set("eff_jingli",(int)ob->query("max_jingli"));
	if ( p == 3 && random (10) == 1 && exp > 1000000)
	me->set("double_attack", 1);
	skills = me->query_skills();
	if (mapp(skills)){
		sk = keys(skills);
		for (i=0;i<sizeof(sk);i++)
			skills[sk[i]] = lv;
	}
	message_vision(HIR""+me->name()+"����$N����һ����Ц��˵������Ȼ�������" + RANK_D->query_rude(ob)+ "ײ���ˣ���Ҳ��ֻ�����������ˣ�\n\n"NOR,ob);
	me->kill_ob(ob);
	remove_call_out("checking");
	call_out("checking", 1, me, ob);     
}

void dest()
{
	destruct(this_object());
}

void do_lost()
{
	object me,ob;
	me = this_object();
	ob = find_player(me->query_temp("target"));
	if(!ob) return;
	ob->set("wd/wd_job_lost",1);
	tell_room(environment(me), "\n"+me->query("name")+"��һ�������Ӳ������ˣ�ת��������Ͳ����ˡ�\n");
	destruct(me);
}

void kill_ob(object ob)
{
	object obj,pp;
	obj = this_object();
	pp = find_player(obj->query_temp("target"));
	if(!ob || !pp) return;
	if(obj->query_temp("target") != ob->query("id")){
		pp->set("wd/wd_job_lost2",1);
		tell_room(environment(obj), obj->query("name")+"���µ����ú�������ǰ����������\n", ({obj}));
		tell_room(environment(obj), obj->query("name")+"ת��������Ͳ����ˡ�\n", ({obj}));
		tell_object(pp, YEL"\n"+ob->query("name")+"("+capitalize(ob->query("id"))+")·����ƽ���ε��������Ѿ������"
		+pp->query("wd/wd_job_place")+YEL"�Ķ���"+obj->query("name")+"�����ˡ�\n\n"NOR);
		write_file( "/log/job/wd_job",sprintf("%s %s(%s)����%s(%s)��robber��\n", ctime(time()),
			 ob->name(),ob->query("id"), pp->query("name"),pp->query("id")));
		destruct(obj);
		return;
	}
	::kill_ob(ob);
}

void unconcious()
{
	object me,ob;

	me = this_object();
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		destruct(me);
		return;
	}
	if (!present(ob)) {
		ob->set("wd/wd_job_lost2",1);
		tell_room(environment(me), "\n"+me->query("name")+"��һ�������Ӳ������ˣ�ת��������Ͳ����ˡ�\n");
		destruct(me);
		return;
	}
	ob->set("wd/wd_jobok",1);
	tell_room(environment(me), "\n"+me->query("name")+"��һ�������ã���ת��������Ͳ����ˡ�\n");
	destruct(me);
}

void die()
{
	object me,ob;

	me = this_object();
	ob = find_player(me->query_temp("target"));
	if (!ob) {
		destruct(me);
		return;
	}
	if (!present(ob)) {
		ob->set("wd/wd_job_lost2",1);
		tell_room(environment(me), "\n"+me->query("name")+"��һ�������Ӳ������ˣ�ת��������Ͳ����ˡ�\n");
		destruct(me);
		return;
	}
	ob->set("wd/wd_jobok",1);
	::die();
}

int checking(object me, object ob)
{
	if(!me) return 0;
	if((!me->query("qi") >= me->query("max_qi")/2) && (me->query_temp("cure") < 2)){
		 me->add("qi",me->query("max_qi")/4);
		 me->add_temp("cure",1);
		 tell_room(environment(me), me->query("name")+"��������˿�������ɫ��ʱ������ࡣ\n", ({me})); 
	}

	if(!ob || environment(ob)!= environment(me)){
		 remove_call_out("do_lost"); 
		 call_out("do_lost",0);
		 return 1;
	}
	else if(ob->is_fighting(me)){
		 remove_call_out("checking");
		 call_out("checking", 1, me, ob);
		 return 1;
	}
	else if(!me->is_killing(ob->query("id"))){
		 me->kill_ob(ob);
		 remove_call_out("checking");
		 call_out("checking", 1, me, ob);
		 return 1;
	}
	return 1;
}
