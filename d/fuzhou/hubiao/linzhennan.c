// linzhennan.c ������
// modified by XiaoYao 98/12/16

#include <ansi.h>

inherit NPC;

int ask_fuwei();
int ask_yuantu();
int ask_pixie();
int ask_tong();
int test_dart();
int checkvaild(object ob);

void create()
{
	set_name("������", ({ "lin zhennan", "lin", "zhennan" }));
	set("gender", "����");
	set("age", 45);
	set("long", "�����ǡ������ھ֡�������ͷ���������ϡ�\n");

	set("combat_exp", 30000);
	set("shen_type", 1);

	set("max_neili", 500);
	set("jiali", 10);
	set("no_get","�����϶�����˵̫���ˡ�\n");

	set_skill("force", 40);
	set_skill("sword", 50);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);

	set("inquiry", ([
		"������լ" : "�����Ҵ�ǰ�ڸ���ʱס�ļ�Ժ���Ѿ��ư��ˡ�",
		"�����ھ�" : (: ask_fuwei :),
		"Զͼ��" : (: ask_yuantu :),
		"��Զͼ" : "�ߣ�С������ôû��ò��ֱ���������䣡",
		"��а����" : (: ask_pixie:),
		"ͭǮ" : (: ask_tong:),
		"ͭ��" : (: ask_tong:),
		"Ѻ��" : (: test_dart :),
		"����" : (: test_dart :),
	]) );

	set("chat_chance", 2);
	set("chat_msg", ({
		"������˵����������ھ����ⲻ��\n",
	}) );
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 15);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}

int ask_fuwei()
{
	say(
		"��������ҫ��˵�������ּ��������ڣ�һ����������Զͼ�����괳�µ���������\n"
		"�����������ּҼҴ������ն����㺬��������н��յľ��棬��Ϊ����������\n"
		"һָ�Ĵ��ھ֡��������ᵽ�������ھ֡����֣�˭��Ҫ�����Ĵָ��˵һ������\n"
		"�ø����������磡��������������\n"
	);
	this_player()->set_temp("marks/��1", 1);
	return 1;
}

int ask_yuantu()
{
	if (this_player()->query_temp("marks/��1")) {
		say(
			"�����Ͽ�һ���̶���˵����Զͼ�����ҵ��游�������ھ�����һ�ִ���ġ�����\n"
			"�游����ʮ��·��а���������ھ֣������Ǵ��ڵ��޵��֡���ʱ�׵���Ӣ�ۼ�\n"
			"��̫�����磬Ҳ��ȥ�����������յģ�����������������ʦ������������֮ʱ\n"
			"��������а���������˼��С�\n"
		);
		this_player()->set_temp("marks/��2", 1);
		return 1;
	}
	say("������˵����Զͼ�����ҵ��游��\n");
	return 1;
}

int ask_pixie()
{
	int p1, p2, p3, p4;

	if (this_player()->query("combat_exp") < 100000) {
		message_vision(
			HIY "$N��Ȼ��ŭ���ȵ�����Ҳ���������ּҵı�а���ף����Ҹ���ƴ�ˣ�\n" NOR,
			this_object()
		);
		kill_ob(this_player());
	} else {
		if (this_player()->query("passwd"))
			say("�����ϲ��õ�˵�����Ҳ��Ƕ������������ҵĽ����������档\n");
		else if (this_player()->query_temp("marks/��2")) {
			say(
				"������һ����˵��������ô֪���ģ��ޣ��Ҹղ�˵¶���ˡ��ˣ����µĹ�������\n"
				"��֪��ϸ����ʵ���������档��\n"
			);
			write("�����϶�һ�٣����Ŷ������˵������ȥ��ǰ�������Ҹ�����");
			p1=random(4)+1;
			p2=random(4)+1;
			p3=random(4)+1;
			p4=random(4)+1;
			this_player()->set("passwd", p1*1000+p2*100+p3*10+p4);
			write(chinese_number(this_player()->query("passwd")));
			write("��ͭǮ����һֱδ�����а��ء�\n");
		} else {
			message_vision(
				HIY "$N��Ȼ��ŭ���ȵ�����Ҳ���������ּҵı�а���ף����Ҹ���ƴ�ˣ�\n" NOR,
				this_object()
			);
			kill_ob(this_player());
		}
		this_player()->delete_temp("marks/��1");
		this_player()->delete_temp("marks/��2");
	}
	return 1;
}

int ask_tong()
{
	int p;

	if (!(p=this_player()->query("passwd")))
		say("������һ����Ц�����ӣ�˵����ô�쵽��һ���˵���ҪǮ��\n");
	else {
		write("�����ϵ���˵������ȥ��ǰ�������Ҹ�����");
 		write(chinese_number(p));
 		write("��ͭǮ����һֱδ�����а��ء�\n");
	}
	return 1;
}

int do_accept(string arg)
{
	object ob,cart,biaotou,cloneobj;
	object me,*team,maxplayer,weaponobj;
	int totalexp=0,maxexp,minexp,lev,attr;
	int size,i;
	string* end= ({ "/d/taishan/sjzhuang","/d/xingxiu/xiaowu","/d/shaolin/jxzhuang",
			"/d/hengshan/sanjiaodian","/d/dali/dafujia","/d/xiangyang/shide",
			"/d/huanghe/huanghegate","/d/emei/lingwenge","/d/dali/wuliang/jhg",
			"/d/wudang/sanqingdian","/d/tls/shiyuan","/d/huashan/zhengqi" });
	string* endname= ({ "̩ɽ����ׯ","����С��","���־���ׯ","��ɽ���̵�","�����֮��",
			    "�¼�������","�ƺӰ�կ��","�������ĸ�","����������","�䵱�����",
			    "���ʴ�ʿԺ","��ɽ������" });
	int* timexs= ({ -5,5,0,15,5,-5,0,5,5,5,10,5 });
	mapping skl;
	int * levs,teams,xs;
	string addr,weapon;
	mapping skill_status, map_status;
	string *sname, *mname,* tempstr;
	object* obj;
	string* weapontype=({ "whip","sword","blade","hammer","axe","stick","throwing","staff",
			      "club" });
	string* weaponfile= ({ "bian","changjian","blade1","chui","dafu","zhubang",
			       "feihuangshi","gangzhang","gun" });
	string* emptyhand=({ "cuff","strike","finger","hand","leg","claw" });
	string* clone1=({ "/d/thd/npc/yaoshi","/d/mr/npc/murong-bo","/d/tls/npc/kurong",
			    "/d/dali/wangfu/npc/dzc","/kungfu/class/shaolin/du-nan",
			    "/kungfu/class/gumu/yang","/kungfu/class/gaibang/h7g",
			    "/kungfu/class/emei/mie-jue","/d/huashan/npc/yuebuqun",
			    "/kungfu/class/wudang/zhang"});
	mixed *local = localtime(time() * 60);

	if (arg != "quest") return 0;
	me=this_player();
/*	if ((local[2] < 6 || local[2] >= 21) && !wizardp(me)) {
		command("say ҹ�令�ڣ�ʵ��̫��Σ�գ��ҷ��Ĳ��¡�");
		return 1;
	}*/
	if (sizeof(filter_array(children(__DIR__"obj/cart"), (: clonep :))) > 7)
	{
		command("say ���������Ѿ����˽�����֧���ˡ�");
		return 1;
	}

	team=me->query_team();
	if (sizeof(team)<2 )
	{
		command("say ����·;Σ�գ�����ô�ٵ��ˣ��ҿɲ����ġ�");
		return 1;
	}
	else if(sizeof(team)>4)
	{
		command("say ����·;Σ�գ������˶���û�õġ�");
		return 1;
	}
	if (team[0]!=me) {
		command("say ֻ�ж����������������ڡ�");
		return 1;
	}
	for (i=0;i<sizeof(team);i++)
	{
		if (!team[i])
		{
			command("say ��Ķ�����������⣬���ɢ�������齨��");
			return 1;
		}
		if (team[i]->query_temp("protecting")) {
			command("say �ţ���Ķ�������ô�����̰��֮�ˣ�");
			return 1;
		}
		if (!present(team[i]))
		{
			command("say �ף���ô�����˲�ȫ����"+team[i]->query("name")+"��ôû����");
			return 1;
		}
		if (team[i]->query("job_name") == "���ݻ���" && !wizardp(team[i])){
			command("say һֱ���ں�����ģ��ҿ���λ"+team[i]->query("name")+RANK_D->query_respect(team[i])+"����ȥЪϢƬ�̰ɣ�");
			return 1;
		}
		if (team[i]->query_condition("job_busy") && !wizardp(team[i])){
			command("say һֱ���ں�����ģ��ҿ���λ"+team[i]->query("name")+RANK_D->query_respect(team[i])+"����ȥЪϢƬ�̰ɣ�");
			return 1;
		}
                if (me == team[i]) continue;
		if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
			command("say �㻹�ǽ�"+team[i]->query("name")+"���������˰ɡ�");
			return 1;
		}
	}
	maxexp=minexp=team[0]->query("combat_exp");
	maxplayer=team[0];
	for (i=0;i<sizeof(team);i++)
	{
		/*if (team[i]->query("combat_exp")<150000)
		{
			command("say ����·;Σ�գ��ҿ���λ"+RANK_D->query_respect(me)+"��Ҫһ���ô��");
			return 1;
		}*/
		if (team[i]->query("balance")<1000000)
		{
			command("say ������Σ�յ��£��ҿ�"+RANK_D->query_respect(team[i])+"û���⳥������");
			return 1;
		}
		totalexp=totalexp+team[i]->query("combat_exp");
		if(team[i]->query("combat_exp")>maxexp)
		{
			maxexp=team[i]->query("combat_exp");
			maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp")<minexp)
			minexp=team[i]->query("combat_exp");
	}

	if((totalexp<1500000) || ((maxexp-minexp) > 1000000))
	{
		command("say ����·;Σ�գ��ҿ���λ�ƺ��޴�������");
		return 1;
	}

	teams=sizeof(team);
	//ѡ����Ŀ�� start
	size=sizeof(end);
	i=random(size);
	addr=end[i];
	xs=timexs[i]*60;
	//ѡ����Ŀ�� end
	command("say �뻤����һ��������"+endname[i]+"��\n");
	log_file("job/hubiao",sprintf("%s %s(%s)������������õ��������񣬹�%s��������Ҫ�ʹ�%s��\n",
		ctime(time())[4..19],me->name(1),
		capitalize(me->query("id")),
		chinese_number(sizeof(team)),endname[i]));

	message_vision("$N���ڶӴ����Ѻ�𽻸�$n��\n", me, this_object());
	say("һ���ڳ�����Ժʻ����\n");

	ob=new(__DIR__"obj/cart");
	cart=ob;
	cart->set("long", cart->query("long")+"������д��"+endname[i]+"�����֡�\n");
	cart->set("teamhead",me->query("name"));
	for(i=0;i<sizeof(team);i++) {
		team[i]->set_temp("protecting",cart);
		team[i]->add("balance", -1000000);
		team[i]->apply_condition("job_busy", 45);
		team[i]->set("job_name", "���ݻ���");
		team[i]->set_temp("death",team[i]->query("death_count"));
	}
	ob->move(environment());
	cart->set_temp("teams",teams);
	if(teams>3)
		cart->set_temp("team4",team[3]);
	if(teams>2)
		cart->set_temp("team3",team[2]);
	if(teams>1)
		cart->set_temp("team2",team[1]);
	if(teams>0)
		cart->set_temp("team1",team[0]);
	skl = maxplayer->query_skills();
	if(!sizeof(skl))
		lev=100;
	else {
		levs=values(skl);
		lev=0;
		for(i=0;i<sizeof(levs);i++)
		{
			if(levs[i]>lev)
				lev=levs[i];
		}
	}
	attr=lev*10;
	biaotou=new(__DIR__"biaotou");
	biaotou->move(environment());
	biaotou->set_temp("protecting",cart);
	biaotou->set("combat_exp",maxplayer->query("combat_exp"));

	i=random(sizeof(clone1));
	if(!objectp(cloneobj=find_object(clone1[i])))
		cloneobj=load_object(clone1[i]);
	if ( mapp(skill_status = cloneobj->query_skills()) ) {
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			biaotou->set_skill(sname[i], lev);
		}
	}

	map_status = cloneobj->query_skill_map();
	mname  = keys(map_status);

	for(i=0; i<sizeof(map_status); i++) {
		biaotou->map_skill(mname[i], map_status[mname[i]]);
	}
	obj = all_inventory(maxplayer);
	for(i=0; i<sizeof(obj); i++)
	{
		if((weapon=obj[i]->query("skill_type")) && map_status[weapon]
		    && !obj[i]->query("treasure") && !obj[i]->query("unique")
		    && (obj[i]->query("weapon_prop/damage")>=30) )
		{
			//biaotou->prepare_skill(weapon,map_status[weapon]);
			weapon=file_name(obj[i]);
			tempstr=explode(weapon,"#");
			weapon=tempstr[0];
			weaponobj= new(weapon);
			if (!weaponobj)  return notify_fail("�쳣����\n");
			weaponobj->move(biaotou);
			weaponobj->wield(biaotou);
			break;
		}
	}
	if(i>=sizeof(obj))
	{
		for(i=0;i<sizeof(weapontype);i++)
		{
			if(map_status[weapontype[i]])
			{
				weapon="/clone/weapon/"+weaponfile[i];
				weaponobj= new(weapon);
				if (!weaponobj)  return notify_fail("�쳣����\n");
				weaponobj->move(biaotou);
				weaponobj->wield(biaotou);
				//biaotou->prepare_skill(weapontype[i],map_status[weapontype[i]]);
				break;
			}
		}
	}
	for(i=0;i<sizeof(emptyhand);i++)
	{
		if(map_status[emptyhand[i]])
		{
			biaotou->prepare_skill(emptyhand[i],map_status[emptyhand[i]]);
		}
	}
	biaotou->set("max_qi",attr+100*random(16));
	biaotou->set("eff_qi",biaotou->query("max_qi"));
	biaotou->set("qi",biaotou->query("max_qi"));
	biaotou->set("max_jing",attr+100*random(16));
	biaotou->set("eff_jing",biaotou->query("max_jing"));
	biaotou->set("jing",biaotou->query("max_jing"));
	biaotou->set("max_neili",attr+100*random(16));
	biaotou->set("neili",biaotou->query("max_neili"));
	biaotou->set("eff_jingli",attr+100*random(16));
	biaotou->set("jingli",biaotou->query("eff_jingli"));
	biaotou->set("jiali",lev/5+random(51));
	biaotou->set_temp("apply/damage", lev/3);
	biaotou->set_temp("apply/armor", lev/2);

	ob=new("/clone/money/silver");
	ob->set_amount(100+random(100));
	ob->set("name","����");
	ob->move(cart);

	ob=new(__DIR__"biaoshi");
	ob->remove_all_enemy();
	ob->remove_all_killer();
	ob->move(environment());
	//ob->set_leader(biaotou);
	ob->set_temp("protecting",cart);

	ob=new(__DIR__"biaoshi");
	ob->remove_all_enemy();
	ob->remove_all_killer();
	ob->move(environment());
	//ob->set_leader(biaotou);
	ob->set_temp("protecting",cart);

	me->set_temp("target",addr); //����Ŀ��
	me->set_temp("biao_time",time()+xs);
	return 1;
}

int test_dart()
{
	object ob = this_player();

	if (ob->query_condition("job_busy") || ob->query_temp("protecting") || random(100)>50)
	{
		command("say ����û������Ҫ�ͼ�"+RANK_D->query_respect(ob)+"����");
		return 1;
	}

	command("say ���ڱ��ھ���һ��������Ҫ�˵��־֡�");
	do_accept("quest");
	return 1;
}
