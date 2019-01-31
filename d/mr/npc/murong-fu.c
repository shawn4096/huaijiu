// /d/mr/npc/murong-fu.c  Ľ�ݸ�
// by leontt /12/05/2000
// by tiantian@sj 6/3/2000 fix mr job bug
// Modify By River@SJ ���� job����������drugȫ��cut 12/08/Y2k

inherit NPC;
#include <ansi.h>
#include <combat.h>
#include "skill.h"
int ask_fuming(string arg);
mixed ask_bo();
string ask_fenglu();
mixed ask_sword2();
string ask_skill();
string ask_wang();
string ask_learn();
string ask_dan();
string ask_dan1();
string ask_ge();
string ask_sword();
string ask_book();
string ask_book2();
string ask_times();
string ask_9dan();
int ask_fangqi();

void create()
{
	object weapon;
	set_name("Ľ�ݸ�",({"murong fu","murong","fu"}));
	set("title","����Ľ�ݹ���");
	set("nick","�Ա�֮�� ��ʩ����");
	set("long",
		"���������ºų��Ա�֮������ʩ����Ĺ���Ľ�ݸ���\n"
		"�����ϴ��Ų���һ����Ц�ݡ�\n");
	set("age", 27);
	set("attitude", "friendly");
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("no_get", "Ľ�ݸ�����������\n");

	set("max_qi",3500);
	set("max_jing", 3000);
	set("eff_jingli", 4000);
	set("neili",3500);
	set("max_neili", 3500);
	set("jiali", 1);
	set("combat_exp", 1500000);
	set("dan", 10);
	set("shen", -1000);
	set("no_bark",1);
	set("chat_chance_combat", 25);
	set("chat_msg_combat", ({
		(: exert_function, "shenyuan" :),
		(: perform_action, "strike.riyue" :),
		(: perform_action, "finger.ci" :),
		(: perform_action, "sword.lianhuan" :),
	}));
	set_skill("strike",170);
	set_skill("finger",170);
	set_skill("dodge",180);
	set_skill("force", 170);
	set_skill("canhe-zhi", 160);
	set_skill("murong-jianfa",170);
	set_skill("shenyuan-gong", 180);
	set_skill("yanling-shenfa", 160);
	set_skill("xingyi-zhang",170);
	set_skill("douzhuan-xingyi", 180);
	set_skill("parry", 180);
	set_skill("sword", 270);
	set_skill("literate", 170);
	set_skill("murong-daofa", 160);
	set_skill("blade",160);
	set_skill("xingyi-jianzhen",170);

	map_skill("blade", "murong-daofa");
	map_skill("finger", "canhe-zhi");
	map_skill("force", "shenyuan-gong");
	map_skill("dodge", "yanling-shenfa");
	map_skill("strike", "xingyi-zhang");
	map_skill("parry", "murong-jianfa");
	map_skill("sword", "murong-jianfa");

	prepare_skill("finger","canhe-zhi");
	prepare_skill("strike","xingyi-zhang");

	create_family("����Ľ��", 2, "����");

	set("inquiry",
		([
			"name" : "�Ҿ����Ա�֮������ʩ����Ĺ���Ľ�ݸ���\n",
			"here" : "�����Ǵ��������������룬�ѵ���û����˵����\n",
			"rumors" : "�Ҹ�ͻȾ�񼲣����������˼����һ�涼û���������¶������Σ�\n",
			"����" : "�ҵĹ���ס����٢��ɽׯ���������������µ������񶴡�\n",
			"��ʩˮ��" : (: ask_ge :),
			"Ľ�ݲ�" : (: ask_bo :),
			"����" : (: ask_book :),
			"ٺ»" : (: ask_fenglu :),
			"������" : (: ask_wang :),
			"����" : (: ask_sword2 :),
			"����" : (: ask_sword :),
			"����" : (: ask_times :),
			"��ת����"  : (: ask_skill :),
			"ͼ��" : (: ask_book2 :),
			"��ѧ" : (: ask_learn :),
			"����" : (: ask_fuming :),
			"����" : (: ask_fangqi :),
		])
	);
	set("dan_count", 2);
	set("book_count",1);
	set("book2_count" ,1);
	set("dan1_count", 2);
	setup();
	if (clonep()) {
		weapon = unew(BINGQI_D("sword/biyu-jian"));
		if (!weapon) weapon = unew(BINGQI_D("changjian"));
		weapon->move(this_object());
		weapon->wield();
		add_money("gold", 5);
	}
}
void init()
{
	::init();
	add_action("do_jiaoliang", "jiaoliang");
}

void attempt_apprentice(object ob)
{
	if (ob->query_skill("parry", 1) < 120) {
		command("say �ҹ���Ľ���Ա�֮������ʩ������м�Ҫ�����ߡ�");
		command("say " + RANK_D->query_respect(ob) + "�Ĺ���������������ذɡ�");
		return;
	}

	if (ob->query_skill("shenyuan-gong", 1) < 100) {
		command("say �ҹ���Ľ���Ա�֮������ʩ������ڹ��ķ�Ҫ�����ߡ�");
		command("say " + RANK_D->query_respect(ob) + "�Ĺ���������������ذɡ�");
		return;
	}

	command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
	command("say �������ϣ����ҹ���Ľ���ֵ�һ���ģ�Ϊ�����Ҵ������һ��������");
	command("chat* ����˵��������������һ���ģ������˸�ָ�տɴ�����");
	command("chat* haha");
	command("recruit " + ob->query("id"));
}

string ask_fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if ( !fam || fam["family_name"] != "����Ľ��")
		return "��λ"+ RANK_D->query_respect(ob) +"������Ľ�ݵ��ӣ��˻��Ӻ�˵��";
	switch ( fam["generation"] ) {
		case 2:
			gold += 1000;
		case 3:
			gold += 1500;
			break;
		default:
			return "��λ"+ RANK_D->query_respect(ob) +"���ҹ���Ľ�ݵ����̫�ͣ����ڻ�û���ʸ���ȡٺ»��";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "��λ"+RANK_D->query_respect(ob) +"�����Ѿ����ٺ»�ˣ����ǵ��¸��������ɡ�";
	gold *= ob->query_skill("shenyuan-gong",1);
	if (gold < 1) return "�������û��ٺ»��";
	ob->set("fenglu", fenglu);
	command ("addoil " + ob->query("id"));
	ob->add("balance", gold);
	return "�㱾�µ�ٺ»"+MONEY_D->money_str(gold)+"�Ѿ�����Ǯׯ�ˣ���Ը��λ"+ RANK_D->query_respect(ob) +"��Ҫʹ��ʧ�����úøɰɣ�";
}

mixed ask_sword2()
{
	object me=this_player(), weapon;
	mapping fam;

	if (!(fam = me->query("family")) || fam["family_name"] != "����Ľ��")
		return RANK_D->query_respect(me)+"�뱾��������������֪�˻��Ӻ�̸��";
	weapon = present("biyu jian", this_object());
	if(!objectp(weapon))
		weapon = unew(BINGQI_D("sword/biyu-jian"));
	if(!objectp(weapon))
		return "�����Ѿ�����������, ���ڲ��������";
	command("unwield biyu jian");
	weapon->move(me);
	command("wield jian");
	message_vision("$N����$nһ�ѱ��񽣡�\n", this_object(), me);
	return 1;
}

string ask_wang()
{
	mapping fam;

	if (!fam = this_player()->query("family") || fam["family_name"] !="����Ľ��")
		return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
	return "�������ұ��ã�һֱ������ܵĺ��ϣ����Ҷ��ܳ�ʱ��û�м������ˡ�";
}

string ask_skill()
{
	mapping fam;

	if (!(fam = this_player()->query("family"))|| fam["family_name"] != "����Ľ��")
		return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
	return "��ת��������Ľ�ݼҵľ�ѧ������ע���мܺ�����";
}

string ask_ge()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "����Ľ��")
		return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
	return "��ʩˮ������Ľ���ղ������ؼ�֮���ڣ����ҵ��顭��";
}

string ask_sword()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "����Ľ��")
		return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";
	return "��������ү�����ź��������ð�������������úñ��ܣ�";
}

string ask_book()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "����Ľ��")
		return RANK_D->query_respect(me) +
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(me) + "��������������̸������";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(me) +
		"�������ϲ����ж�ת���Ƶ��伮������ô����Ҫ�ˣ� ����̰�����ᣡ";

	ob = unew("/d/mr/obj/shu1");
	if(!clonep(ob))
		return "��ת�����伮�Ѿ�������Ҫ���ˡ�";

	ob->move(me);

	message_vision("$N�õ�һ����ת���Ƶ��书�ؼ���\n", me);
	return "�ðɣ�����ΪĽ�ݼ����Ĺ������Ȿ��ʹ�����ɡ�";
}

string ask_book2()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "����Ľ��")
		return RANK_D->query_respect(me) +
		"�뱾��������������֪�˻��Ӻ�̸��";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(this_player()) + "��������������̸������";

	if (me->query_skill("douzhuan-xingyi",1)<50)
		return RANK_D->query_respect(me) +
		"��������������̸����ȡͼ�⣿";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(this_player()) +
		"���������ϲ����ж�ת���Ƶ��伮�����ô����Ҫ�ˣ� ����̰�����ᣡ";

	ob = unew("/d/mr/obj/shu2");
	if (!clonep(ob))
		return "�Բ��𣬶�ת���Ƶ��伮�Ѿ�������Ҫ���ˡ�";

	ob->move(this_player());
	message_vision("$N�õ�һ����ת���Ƶ��书�ؼ���\n", me);
	return "�ðɣ�����ΪĽ�ݼ����Ĺ������Ȿ��ʹ�����ɡ�";
}

mixed ask_bo()
{
	object me = this_player();
	object ob = this_object();

	if (me->query_temp("marks/ʧ��")) {
		message_vision(
			"$N���з�����������ֱ��$n��һ��һ�ֵ�˵�����Ѿ��������ˣ�����ô������ȥ���������أ�\n",
			ob, me
		);
		return 1;
	}
	if (me->query("family/family_name") != "����Ľ��")
		return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��";

	if (me->query("family/generation") != 3)
		return RANK_D->query_respect(me) + "Ϊ�ο������Ц��";

	if (me->query_temp("marks/bai_bo"))
		return "���Ѿ�����ȥ���Ҹ�������������ѧ�ˣ�";

	message_vision(
		"$N���з�����������ֱ��$n��һ��һ�ֵ�˵�����Ҹ����������֣���������Ի���\n"
		"�����书δ�ɣ���ò�Ҫȥ��ȡ���裻����������ģ��ͺ��ҽ���һ�¡�(jiaoliang)\n",
		ob, me
	);

	me->set_temp("marks/jiao", 1);
	return 1;
}

int do_jiaoliang()
{
	object me, obj, jiaxin;
	int current_qi;
	int i;

	me = this_object();
	obj = this_player();

	if (obj->query_temp("marks/jiao")) {
		message_vision("$N��$n˵���ðɣ��Ǿ���ʦ��ָ�㼸�С�\n", obj, me);
		set("max_qi", 3500);
		set("jiali", 10);
		set("neili", 3500);
		set("max_neili", 3500);
		current_qi = set("qi", 3500);

		i=10;
		obj->delete_temp("marks/jiao");
		while ((obj->query("qi")*100 / (int)obj->query("max_qi")) > 30) {
			if (!present(obj, environment()))
				return 1;
			i--;
			COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
			if (!i || (me->query("qi")*100/current_qi) < 30) {
				message_vision(
					"$N��$n˵����������Ľ�������ֳ����ģ������д����ţ������϶���ǰȥ���֣�\n"
					"���������Ҹ���ϣ�����ܲ�������������Ľ�����ң��⸴�������\n",
					me, obj
				);
				jiaxin = new("/d/mr/obj/jiaxin");
				jiaxin->move(obj);
				obj->set_temp("marks/bai_bo", 1);
				message_vision("$N����$nһ�����\n", me, obj);
				return 1;
			}
			COMBAT_D->do_attack(me, obj, me->query_temp("weapon"), 1);
		}
		message_vision(
			"$N����$n����˵�������书δ�ɣ��ͺø���Զ���㻹�ǰ�������ȥ�ɣ�\n",
			me, obj
		);
		obj->set_temp("marks/ʧ��", 1);
	}
	return 1;
}

string ask_learn()
{
	int j=random(sizeof(my_skills));
	mapping skill = my_skills[j];
	int i;
	object me = this_player();
	string skill_name;

	i = 7+random(5);
	if (me->query("family/family_name") != "����Ľ��") // ������Ľ���ɵ���
		return RANK_D->query_respect(me) + "�뱾��������������֪�˻��Ӻ�̸��";

	if (me->query("combat_exp") > 2000000 )
		return RANK_D->query_respect(me)
		+ "���Ѿ����������˾���������ѧ��Ҫ���ҿɲ��������Ĵ���ˡ�";

	if (me->query_skill("parry", 1) < 100 ) // �мܱ�����ڵ���100��
		return RANK_D->query_respect(me) +
		"�ڱ�����ѧ�в����������磬���̸������֮��ѧ��";
	if (me->query_skill("douzhuan-xingyi", 1) < 100 )  // ��ת���Ʊ�����ڵ���100��
		return RANK_D->query_respect(me) +
		"�ڱ�����ѧ�в����������磬���̸������֮��ѧ��";
	if (me->query_condition("mr_job") )
		return RANK_D->query_respect(me) +
		"��û����ҽ�����������ء�";
	if (is_fighting())
		return "��ʲô�£�û����������æ������";
	if (me->query("job_name") =="Ľ��͵ѧ")
		return RANK_D->query_respect(me) +
		"�ȵȵȰɣ�������û��ʲô����Ȥ���书��ѧ��";
	if (me->query_condition("wait_mr_job", 1) > 0)
		return RANK_D->query_respect(me) +
		"�ȵȵȰɣ�������û��ʲô����Ȥ���书��ѧ��";

	if(!skill["skill_id"])
		return sprintf("SKILL.H�ļ��ڵ�%d�����ܳ�����֪ͨ��ʦ�޸ġ�\n",j);
	skill_name = to_chinese(skill["skill_id"]);
	me->set_temp("skill_target", skill_name);  // �˱�Ǳ����˴�͵ѧĿ�꼼�ܵ���������
	me->set_temp("skill_id", skill["skill_id"]); // �˱�Ǳ����˴�͵ѧĿ�꼼�ܵ�Ӣ������
	me->set_temp("skill_type", skill["skill_type"]); // �˱�Ǳ����˴�͵ѧĿ�꼼�ܵ�Ӣ������
	me->set_temp("skill_lvl", i); // �˱�Ǳ����˴�͵ѧĿ�꼼������Ҫ�ļ���
	me->apply_condition("mr_job", 30+random(15)); // ���ô˴��������������ʱ�������;
	me->apply_condition("job_busy",9);
	me->set("job_name", "Ľ��͵ѧ");
	command( "whisper "+me->query("id") + " �ҹ���Ľ�ݰ������������书����Ҳ����Ϊ֮��Ľ�ġ�");
	command("whisper "+ me->query("id")
	+ " �ðɣ�"+"��"+skill_name+"��"+"��"+skill["skill_id"]+"���Ҵ����Ѿã����ǰ���ѧ�������Ҵ������͡�");

	new("/d/mr/obj/paper")->move(me);

	if (random(2))
		return "�����������Ǻã����Ǻá�";
	return "���������治��";
}

int ask_fuming(string arg)
{
	object me, ob;
	int bouns,My_exp,Target_exp,pot;
	float rate;

	me = this_player();
	ob = this_object();

	if( !arg)
	{
		command("say ��Ҫչʾʲô��");
		return 1;
	}

	if( !me->query_condition("mr_job"))
	{
		command("say ������û������ɣ�");
		return 1;
	}

	if( me->is_busy())
	{
		command("say ����æ���أ���ʲô���������˵��");
		return 1;
	}

	if( me->is_fighting())
	{
		command("say ��������أ���ʲô���������˵��");
		return 1;
	}

	if(!me->query_temp("job_done"))
	{
		command("say ��ѧ��ʲô�����ˣ��������һ�����");
		return 1;
	}

	if( this_object()->is_fighting())
	{
		command("say ��ʲô�£�û����������æ������");
		return 1;
	}

	Target_exp = me->query_temp("master_exp");
	My_exp= me->query("combat_exp");

	me->add("mr_job",1);
	bouns = me->query_temp("skill_lvl")*5/2;
	bouns +=  me->query_skill("douzhuan-xingyi",1) * 5 / 3;

	rate = to_float(Target_exp)/to_float(My_exp);
	if (rate > 2) rate = 2;
	if (rate < 0.6) rate = 0.6;
	bouns *= rate;

	message_vision(CYN"Ľ�ݸ���ϸ�о���$N����ֽ���ϵ��书��Ҫ���鲻�Խ���˵������һ��"+me->query_temp("skill_target")+"��\n"NOR, me);
	message_vision(CYN"Ľ�ݸ�������$N��ͷ����$P˵�����������ˣ���ȥ��Ϣ�ɡ�\n"NOR, me);
	if (bouns > 800) bouns = 600 + random((bouns-250)/5);
	me->add("combat_exp", bouns);
	me->improve_skill("douzhuan-xingyi", me->query_int()*2);
	pot = bouns/6+random(bouns/10);
	if (me->add("potential", pot) > me->query("max_pot"))
		me->set("potential", me->query("max_pot"));
	write(GRN"������"+(string)(bouns)+"�㾭���"+pot+"��Ǳ�ܵĽ���\n"NOR);
	write(GRN"���Ѿ�ΪĽ����������"+me->query("mr_job")+"������!\n"NOR);

	log_file("job/mrjob",
	sprintf("%s(%s) touxue %s(%s) on %s, exp=%d,job times=%d.\n",
		me->name(1), geteuid(me),
		me->query_temp("skill_target"), me->query_temp("skill_id"), ctime(time()), bouns,me->query("mr_job")));

	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(10)+5);

	if(present("paper", me))
	{
		destruct(present("paper",me));
	}

	return 1;

}

int ask_fangqi()
{
	object me=this_player(),obj;

	if( !me->query_condition("mr_job") )
	{
		command("say ������û������ɣ�");
		return 1;
	}

	command( "say Ҳ�ã���ô������ȥ��Ϣһ��ɡ�" );
	command( "disapp");
	command( "sigh "+me->query("id"));
	obj=me->query_temp("dizi");
	if( objectp(obj) )
		destruct(obj);
	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(2)+2);
		me->add("combat_exp",-10-random(10));
		return 1;
}

string ask_times()
{
	object ob;
	ob = this_player();
	if(!ob->query("mr_job"))
	{
	 return "���ź���"+ob->name()+"�������û��ΪĽ���������ף�";
	}
	return ""+ob->name()+"�����Ѿ������"+CHINESE_D->chinese_number((int)ob->query("mr_job"))+"��Ľ��͵ѧ����";
}
