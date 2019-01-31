// bai.c ������
// By Looklove@SJ 2000/9/27
// Looklove modified 2001.5.25 �Ƕ���

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_dao();
object ppl;
int ask_rumors(object);


void create()
{
        set_name("������", ({ "bai shijing", "bai"}));
        set("title", "ؤ��ִ������");
        set("gender", "����");
        set("age", 47);
        set("long", "������ؤ���е�ִ�����ϣ�����������˽��\n"
        	    "���д�С�˵ȣ���Ȼ����Υ�����������������Ҳ�Ǿ������֡�\n");
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("apprentice",1);
        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 3400);
        set("max_neili", 3400);
        set("jiali", 100);

        set("combat_exp", 1500000);

        set_skill("force", 150); 		// �����ڹ�
        set_skill("huntian-qigong", 150); 	// ��������
        set_skill("dodge", 150); 		// �����Ṧ
        set_skill("xiaoyaoyou", 150); 		// ǧ������
        set_skill("parry", 150); 		// �����м�
        set_skill("strike", 150);
        set_skill("lianhua-zhang",150);
        set_skill("begging", 90);
        map_skill("force", "huntian-qigong");
        map_skill("parry","lianhua-zhang");
        map_skill("strike","lianhua-zhang");
        map_skill("dodge", "xiaoyaoyou");
        prepare_skill("strike", "lianhua-zhang");

        create_family("ؤ��", 18, "�Ŵ�����");

        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "�Ƿ�" : "�ǰ����Ǹ��ú���\n",
                "����" : "���������Ƿ壬���ǵ�ǰ�ΰ�����\n",
	        "����" : (: ask_dao :),
	        "rumors" : (: ask_rumors :),
        ]));
        setup();
        carry_object("/kungfu/class/gaibang/obj/bainayi")->wear();
        carry_object("/kungfu/class/gaibang/obj/gb_budai9")->wear();
}
void attempt_apprentice(object ob)
{
        if (ob->query("family/family_name")
        && ob->query("family/family_name") != "ؤ��") {
                command("say �㻹��ȥ������ɿ����ɡ�");
                return;
        }
        if ((int)ob->query("gb_bags") >= 2
        && ob->query("family/family_name") != "ؤ��" ) {
                command("say ؤ����ݲ��������ֱ��������С�ˣ�");
                command("kill "+ob->query("id"));
                return;
        }
        if ((int)ob->query("gb_bags") < 3
        || ob->query("gb_job") < 300 ){
                command("say ���ڰ��е�������ǳ����Щ������˵�ɣ�");
                return;
        }
        if (ob->query("shen")< ob->query("combat_exp")/2) {
                command("say ���������ã��ٶ���������°ɡ�");
                return;
        }
        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("ؤ������%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","����");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
string ask_dao()
{
        object me;
        object *list;

        me = this_player();

        if ( me->query("family/family_name") != "ؤ��")
                return RANK_D->query_respect(me) +
                "����ؤ��ú�����֪�˻��Ӻ�̸��";

        if ( me->query("family/master_name")!="������")
                return RANK_D->query_respect(me) +
                "���������õ��ӣ��γ����ԣ�";

        if ( me->query_temp("fadao/asked"))
        	return "�ղ��㲻���ʹ���ô��";

        if ( present("fa dao", me))
                return RANK_D->query_respect(me) +
                "�����㲻����������";

        list = filter_array(objects(), (: $1->query("id")=="fa dao":));
        if ( sizeof(list) > 8) {
        	me->set_temp("fadao/asked",1);
        	return "�����ֵ�����ִ�����Ȼ��";
        }

        new("/clone/weapon/blade/fadao")->move(me);
	me->set_temp("fadao/asked",1);
        message_vision("$N�õ�һ��������\n",me);
        return "�ã������ȥ����Ѳ�ӣ����ֲ��ذ��ĵ��ӣ��͵ش��á�";
}

int ask_rumors(object me)
{
    	int exp;
    	object where, target, *list;

    	me = this_player();
    	if(!me) return 0;

    	me->add_temp("count",1);
    	exp = me->query("combat_exp");

	if((string)me->query("family/family_name")!="ؤ��"){
		command("en "+me->query("id")+"");
		return 1;
	}
	if((string)me->query("family/master_name")!="���߹�"){
		command("pat "+me->query("id")+"");
		return 1;
	}
    	if (query("waiting")) {
        	command("say ��ȵȰɣ����ڵ����ء�");
        	return 1;
        }
	if(me->query_temp("h7g/k_target")||!me->query_temp("h7g/quest")){
		return 1;
	}
    	if (me->query_temp("count") > 3) {
        	me->delete_temp("count");
        	command("say �㻹��һ�������ɡ�\n");
        	return 1;
        }

    	ppl = me;
    	list = filter_array(users(), (:
    				    $1->query("combat_exp")>ppl->query("combat_exp")*3/4
    				 && $1->query("combat_exp")<ppl->query("combat_exp")*5/4
    				 && !wizardp($1)
    				 && interactive($1)
    				 && query_idle($1)<120
    				 && $1->query("PKS")>50
    				 && objectp(environment($1))
    				 && !$1->query_temp("pigging_seat")
    				 && $1->query("family")
   				 && !$1->query_condition("relax")
    				 && !$1->query_condition("wuguan_job")
                                 && $1->query("family/family_name")!="ؤ��"
                                 && $1->query("family/family_name")!="������"
                                 && $1->query("family/family_name")!="�䵱��"
                                :));
    	list -= ({me,0});

    	if(sizeof(list)<random(10)+1){
        command("say ����������ûʲô�£�����������ɡ�\n");
        return 1;
	}
    	target = list[random(sizeof(list))];
    	where = environment(target);
       	command("say ��˵"+HIR+target->query("name")+HIW+"("+target->query("id")+")"+CYN"��������ˣ���ȥ���Ұ������ˣ�");
       	command("say ��ȥ"+HIG+where->query("short")+CYN+"�������ҿ���");
       	target->set_temp("no_zhong",1);
       	target->set_temp("h7g/k_target",1);
       	set("target",target->query("name"));
       	set("targetid",target->query("id"));
       	me->set_temp("h7g/k_target",1);
       	set("waiting",1);
       	return 1;
}



int accept_object(object me, object ob)
{
	int amount;
	object n_money;

	amount = random(100)+100;
    	if (!me->query_temp("h7g/k_target")) {
       		command("say ���������ʲô��");
       		return 0;
       	}
    	if (ob->query("name")==query("target")+"���׼�"
        && ob->query("victim_id")==query("targetid")
        && ob->query("material")=="meat") {
       		command("nod");
       		if (random(2)!=1) {
       			command("say �ã����Ǹ���Ľ��������⣬����������������ȥһ�ˡ�");
       			me->set_temp("h7g/xlz_jobv",1);
                	n_money = new("/clone/money/gold");
                	n_money->set_amount(50);
                	n_money->move(me);
       		}
       		else {
       		command("say �ã����ĺã����Ǹ���Ľ�����");
                n_money = new("/clone/money/gold");
                n_money->set_amount(amount);
                n_money->move(me);
		}
       		set("waiting",0);
       		return 1;
       	}
       	else{
       	command("say ���������ʲô��");
       	return 0;
       	}
}