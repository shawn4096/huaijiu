// modified by explorer, 3/9/97
// cool 99/2/9
// Looklove 2000/8/25
// Looklove Modify at 2001/1/19
// Looklove Modify at 2001/4/7
// Looklove Modify at 2001/5/3

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_ji();
int ask_bag();
int ask_up();

void consider();
int pass_chuanwei(object me, object ob);


void create()
{
    	object ob;

    	set_name("���߹�", ({"hong qigong", "hong", "qigong"}));
    	set("nickname", HIY"��ָ��ؤ"NOR);
    	set("gender", "����");
    	set("age", 65);
    	set("per",24);
    	set("long", "������ؤ���ʮ���ΰ������ųơ���ؤ���ĺ��߹���ү�ӡ�\n");
    	set("attitude", "friendly");
        set("no_bark",1);
        set("dgb/wugou",6);
        set("str", 30);
        set("con", 30);
        set("dex", 30);
    	set("int", 22);
    	set("max_qi", 8800);
    	set("max_jing", 3600);
    	set("neili", 24000);
    	set("max_neili", 13000);
    	set("jiali", 200);
    	set("eff_jingli",4000);
    	set("combat_exp", 5400000);

    	set_skill("force", 300);
    	set_skill("huntian-qigong", 300);    // ��������
    	set_skill("strike", 300);            // �����Ʒ�
    	set_skill("xianglong-zhang", 300);   // ����ʮ����
        set_skill("literate",150);           // ��д
    	set_skill("dodge", 300);             // ��������
    	set_skill("xiaoyaoyou", 300);        // ��ң��
    	set_skill("parry", 300);             // �����м�
    	set_skill("stick", 300);             // ��������
    	set_skill("dagou-bang", 300);        // �򹷰���
    	set_skill("begging", 200);           // �л�����
    	set_skill("checking", 200);          // ����;˵
    	set_skill("bangjue",200);            // ����
    	set_skill("dagou-zhen",200);	     // ����
        set_skill("lianhua-zhang",300);      // ������
        set_skill("stealing",200);           // hehe

    	map_skill("force", "huntian-qigong");
    	map_skill("strike", "xianglong-zhang");
    	map_skill("dodge", "xiaoyaoyou");
    	map_skill("parry", "dagou-bang");
    	map_skill("stick", "dagou-bang");
    	prepare_skill("strike", "xianglong-zhang");

    	set("chat_chance_combat", 100);
    	set("chat_msg_combat", ({
        	(: perform_action, "strike.xiao" :),
        	(: perform_action, "stick.chan" :),
        	(: perform_action, "stick.ban" :),
        	(: perform_action, "stick.yin" :),
        	(: perform_action, "stick.pi" :),
        	(: perform_action, "stick.shuangjue" :),
        	(: exert_function, "powerup" :),
        	(: perform_action, "strike.paiyun" :),
        	(: perform_action, "strike.kanglong" :),
		(: perform_action, "strike.xiao" :),
        }));

    	set("chat_chance", 1);
    	set("chat_msg", ({
        	"���߹�̾�˿�����������������ʱ���ٳԵ��ض����ġ��л�������������\n",
        	"���߹�˵�������϶���Ĺ����ռ������������ҵ����취�Ը�������\n",
        	"���߹��૵���������ؤ��ġ�����ʮ���ơ���������Ե����Ʒ�����\n",
        	}));

    	set("inquiry", ([
        	"�϶���" : "�϶�������ҵ�����ͷ���������˳�������ŷ���塣\n",
        	"ŷ����" : "�����ҵ�����ͷ���������˳�������\n",
        	"����" : "���...���...\n",
        	"rumors" : "���û��˵ʲô��Ϣ��\n",
        	"����" : "�����ҵĺ�ͽ���������˱��˵㡣\n",
        	"����" : "��СѾͷ���Ǹ�����������Ŀ��治����\n",
        	"��ҩʦ" : "����������ѧ��ţ������һ��Ǹ�ϲ�����Ǹ�СѾͷ��\n",
        	"��а" : "����������ѧ��ţ������һ��Ǹ�ϲ�����Ǹ�СѾͷ��\n",
        	"�ϵ�" : "������壬���Ҹ��ʡ�\n",
        	"������" : "�ǿ��Ǹ���ѧ��ţ��Ͻл��ɲ��������ܡ�\n",
        	"����ͨ" : "���������ںܶ�����������������Ϊ�Լ�����������������\n",
        	"ؤ��" : "����ؤ�ﶼ��֪�����ҿ����е��㶷�ˣ�\n",
        	"�򹷰�" : "���...���...������Σ�\n",
        	"������" : "û�±��Ҵ�����С����һ�������㡣\n",
        	"�����л�" : "û�±��Ҵ�����С����һ�������㡣\n",
        	"������" : "û�±��Ҵ�����С����һ�������㡣\n",
        	"�л���" : (: ask_ji :),
        	"����":    (: ask_bag :),
        	"��λ":    (: ask_up :),
        	]));

    	create_family("ؤ��", 17, "����");
        set_temp("apply/damage", 70);
        set_temp("apply/dodge", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/armor", 70);

    	setup();

    	if (clonep())
    	{
        	ob = unew(BINGQI_D("yuzhu_bang"));
        	if (!ob) ob = unew(BINGQI_D("zhubang"));
        	ob->move(this_object());
        	ob->wield();
        	carry_object(__DIR__"obj/bainayi")->wear();
        	carry_object(__DIR__"obj/gb_budai10")->wear();
    	}
}

void attempt_apprentice(object ob)
{
    	if ((int)ob->query("gb_job",1) < 400)
    	{
        	command("say  ���ҵĵ���ҪΪؤ�����������" + RANK_D->query_respect(ob) + "�ڰ��еĻ����ƺ�������һЩ��\n");
        	return;
    	}
    	if ((string)ob->query("family/family_name") != "" &&
        (string)ob->query("family/family_name") != "ؤ��")
    	{
        	command("say " + RANK_D->query_respect(ob) + "��Ȼ������ʦָ�㣬�α��������Ͻл��أ�\n");
        	return;
    	}
    	if ((int)ob->query("gb_bags")<6)
    	{
        	command("say " + RANK_D->query_respect(ob) + "�ڰ���ְλ̫�ͣ��ȼ��������ɡ�\n");
        	return;
    	}
    	command("chat ���������Ͻл�����֮ǰ�����ҵ�"+RANK_D->query_respect(ob)+"����һ������֮��,ؤ���������ˡ�\n");
    	command("recruit " + ob->query("id"));

        ob->set("title",sprintf("ؤ���ܶ�%s������",
                chinese_number(ob->query("gb_bags"))));
    	ob->set("class", "beggar");
        ob->set("gb/fenduo","�ܶ�");
        ob->set("gb/alloted",1);
    	return;
}

void init()
{
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");
}
int ask_bag()
{
    	object me=this_player();
    	int bag = me->query("gb_bags");
    	int lvl = bag-5;
    	mapping skl;
    	string *sname;
    	int i;
    	string *skilllimit = ({
        	"begging","bangjue","checking","dagou-zhen","literate",
        	});
    	int *lvllimit = ({
        	200,200,200,200,300,
        	});


    	if( me->query("family/family_name")!="ؤ��" )
    	{
        	command("say " + RANK_D->query_respect(me) + "����ؤ�������������˻���֪�Ӻ�˵��\n");
        	return 1;
    	}
    	if (bag<6)
    	{
        	command("say " + RANK_D->query_respect(me) + "�ڰ���ְλ̫�ͣ��ȼ��������ɡ�\n");
        	return 1;
    	}
    	if( bag==9)
    	{
        	command("say " + RANK_D->query_respect(me) + "�ڰ������ǾŴ����ϣ�������������ȥ��\n");
        	command("sneer "+me->query("id"));
        	me->set("title","ؤ��Ŵ�����");
        	return 1;
    	}
    	if ((int)me->query("shen") < 400000*lvl)
    	{
        	command("say ��ؤ���������������ɣ�"+RANK_D->query_respect(me)
            	+"�Ƿ�Ӧ�ö���������֮�¡�");
        	return 1;
    	}

    	if( me->query("gb_job2") < 100*lvl)
    	{
        	command("say ��ؤ���������������ɣ�"+RANK_D->query_respect(me)
            	+"Ӧ��Ϊ��Ϊ������㹱�ײźá�");
        	return 1;
    	}

    	skl = me->query_skills();
    	if (mapp(skl)) sname = keys(skl);

    	for(i=0; i<sizeof(skl); i++)
    	{
        	me->set_skill(sname[i],skl[sname[i]]+lvl);
    	}

    	for(i=0; i<sizeof(skilllimit); i++)
    	{
        	if( me->query_skill(skilllimit[i])>lvllimit[i] )
            	me->set_skill(skilllimit[i],lvllimit[i] );
    	}

    	me->add("gb_bags",1);
    	bag=bag+1;
    	me->add("max_neili",10*(bag-3));
    	command("applaud " + me->query("id"));
    	if( bag==7)
    	{
        	command("say �ɵúã��ӽ��쿪ʼ�������ؤ��" +
            	chinese_number(bag) +
            		"�����ӣ��úøɣ�\n");
        	me->set("title",sprintf("ؤ���ܶ�%s������",
            		chinese_number(bag)) );
    	}
    	else if(bag==8)
    	{
        	command("say �ɵúã��ӽ��쿪ʼ�������ؤ��" +
            	chinese_number(bag) +
            	"���������úøɣ�\n");
        	me->set("title",sprintf("ؤ��%s������",
            	chinese_number(bag)) );
    	}
    	else if(bag==9)
    	{
        	command("say �ɵúã��ӽ��쿪ʼ�������ؤ��" +
            	chinese_number(bag) +
            	"�����ϣ��úøɣ�\n");
        	me->set("title",sprintf("ؤ��%s������",
            	chinese_number(bag)) );
    	}
    	return 1;
}

int filldata(object obj1)
{
        if(wiz_level(obj1)) return 0;
        if(!environment(obj1)) return 0;
        else return 1;
}



int ask_up()
{
    	object me=this_player(),ob=this_object();
    	int skill, bag = me->query("gb_bags");
    	string *applied_id;

    	mixed *ob_list;
    	int max,i;
    	object obj1;

    	skill = me->query_skill("xianglong-zhang",1);
    	if( me->query("family/family_name")!="ؤ��" )
    	{
        	command("say " + RANK_D->query_respect(me) + "����ؤ�������������˻���֪�Ӻ�˵��\n");
        	return 1;
    	}
    	if( bag<9)
    	{
        	command("say " + RANK_D->query_respect(me) + "�ڰ��е�λ̫�ͣ���λ��������޷�˵���ڵ��ӡ�\n");
        	return 1;
    	}
    	if ((int)me->query("gb_job",1) < 1000)
    	{
        	command("say " + RANK_D->query_respect(me) + "�ڰ��еĻ����ƺ�������һЩ�����������۷��ڵ��ӡ�\n");
        	return 1;
    	}
    	if( me->query("shen")<1500000)
    	{
        	command("say " + RANK_D->query_respect(me) + "���������������������쵼ؤ��������ӡ�\n");
        	return 1;
    	}

    	if(me->query("xy/job")+me->query("gb_job2")<500)
    	{
        	command("say ��ؤ���������������ɣ�"+RANK_D->query_respect(me)
            	+"Ӧ��Ϊ��Ϊ������㹱�ײźá�");
        	return 1;
    	}
    	if( me->query_temp("gb_chuanwei") )
    	{
        	command("say " + RANK_D->query_respect(me) + "�Ѿ���ؤ��������ο��������ҿ���Ц��\n");
        	return 1;
    	}
    	if( me->query_skill("dagou-bang",1)<280 || me->query_skill("xianglong-zhang",1)<280 )
    	{
        	command("say �򹷰����ͽ���ʮ��������ؤ���洫������" + RANK_D->query_respect(me) + "���ⷽ�����Ϊ�Ƿ��Բ���һ�㡣\n");
        	return 1;
    	}

    	if( !present("yuzhu bang",ob) )
    	{
        	command("say �ҵ������������ȥ�ˣ����ˣ����¿�û�취��λ�ˡ�");
        	return 1;
    	}

    	ob_list = users();
    	ob_list = filter_array(ob_list, (: filldata :));
    	max=sizeof(ob_list);
    	for (i=0;i<max;i++)
    	{
        	obj1 = ob_list[i];
        	if (obj1->query_temp("gb_chuanwei") )
        	{
            	command( "say ���Ѿ��Ѱ���֮λ����" + obj1->query("name") +"�ˡ�\n" ) ;
            	return 1;
        	}

    	}

    	command("look "+me->query("id"));
    	command( "say �������²����ȿ�������书��" );

    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;
    	if ( !pass_chuanwei(me, ob ) ) return 1;

    	if( pointerp(applied_id = me->query_temp("apply/id"))
        	 && sizeof(applied_id) )
        	me->set_temp("apply/short",
             ({"ؤ���ʮ�˴�����"+" "+me->name()+"("+applied_id[0]+")"}));
    	else
        {
        	me->set_temp("apply/long",
            	({"ؤ���ʮ�˴�����"+" "+me->name()+"("+me->query("id")+")"}));
        	me->set_temp("apply/short",
            	({"ؤ���ʮ�˴�����"+" "+me->name()+"("+me->query("id")+")"}));
        }
	me->add_temp("apply/strength", skill/10);
    	command("chat �Ͻл����ս�ؤ�����֮λ����"+me->query("name")+"��������ؤ���������ˡ�");
    	message_vision("���߹�����$Nһ���������\n",me);

    	me->set_temp("gb_chuanwei",1);
    	present("yuzhu bang",ob)->move(me);

    	return 1;
}

int pass_chuanwei(object me, object ob)
{
    	COMBAT_D->do_attack(ob, me, ob->query_temp("weapon"), 1);

    	if (!present(me,environment(ob)) || me->query("qi") <= 0
        	|| me->query("jing") <= 0 || me->query("jingli") <= 0)
    	{
        	command("say �书���֮���δ����²�����");
        	ob->reincarnate();
        	return 0;
    	}
    	return 1;
}

int accept_object(object who, object ob)
{
    	object ob_yzz, me = this_object();

    	if (ob->query("food_supply") <= 0)
        	return 0;
    	if ((string)ob->query("name") != "�л���" ||
        	who->query_temp("marks/get-ji"))
    	{
        	command("say �Ͻл���" + (string)ob->query("name") + "ûʲô��Ȥ����");
        	return 0;
    	}

    	if (query("food") >= max_food_capacity() - ob->query("food_supply"))
    	{
        	command("say �Ͻл����ڱ��úܡ�");
        	return 0;
    	}

    	command("say ����������������ԵĽл���ѽ��");
    	command("eat ji");
    	command("say �벻����СС��ͣ���˼ȴ��ϸ���͸�������ض�һ����");
        call_out("dest", 1, ob);

    	if ((string)who->query("family/family_name") != "ؤ��")
    	{
        	command("say " + RANK_D->query_respect(who) + "�㻹���������ʲô��");
        	return 1;
    	}

    	if( ob_yzz = present("yuzhu bang", me) )
    	{
        	ob_yzz->move(who);
        	write("�����������Ҷ����ˣ����͸�����������ɡ�");
        	return 1;
    	}
    	else
    	{
        if((time()-who->query("gb/jitime"))>=100) {
        	who->add("combat_exp",random(200));
        	who->add("potential",random(100));
        	if(who->query("potential")>who->query("max_pot"))
        	who->set("potential",who->query("max_pot"));
        	who->set("gb/jitime",time());
        }
        if(random(150) == 50 && who->query("family")
             && who->query("family/family_name") == "ؤ��"
             && who->query_skill("xianglong-zhang", 1) > 200
             && !who->query("xlz/hang")
             && !who->query_temp("xlz/hang"))
             call_out("kanglong", 10, who, this_object());
             	return 1;
    	}
	return 1;
}

void dest(object obj)
{
            if(!obj) return;
            destruct(obj);
}

int ask_ji()
{
    	object ob;
    	ob=this_player();

    	if (!ob->query_temp("marks/jiaohua-ji"))
    	{
        	command("haha");
        	command("say "+RANK_D->query_respect(ob)+",�Ҹ������,����������óԵĽл��������ض��Ǹ�СѾͷ����!\n");
        	command("say �����ⱿС��Ҳ��֪��������ȥ��?����ȥ�������ض����Ҵ�ֻ��,������Ҳ������.\n");
        	ob->set_temp("marks/jiaohua-ji",1);
        	return 1;
    	}
    	else
    	{
        	command("say ��Ҳ�����?");
        	return 1;
    	}
}

int kanglong(object me, object ob)
{
    	if(!ob || !me || !living(ob) || !living(me)
        	|| environment(ob) != environment(me)
        	|| ob->is_fighting() || me->is_fighting())
        	return 0;

    	command("consider");
    	command("say �����������ǲ������������ͻ�Ѿͷͬ���õ���ζ����");
        if ( me->query("combat_exp") > 2000000 && random((int)me->query_con())>10){
  		command("say ��Ҳ���ܰ׳�����Ĳˣ������ɡ�");
    		command("whisper "+me->query("id")+" ��ȥ����"YEL"��ɳɽ"NOR"ס��һ���ӣ���û���컯�Ϳ����Լ��ˡ�");
    		me->set_temp("xlz/hang", 1);
		return 1;
        }
        else
        command("say �������ʲ������Ժ󹦷������������Ұɡ�");
        command("whisper "+me->query("id")+" ��ʱ��ǵ��ٸ��Ҵ���ֻ�л�����ζ������hoho��");
        return 1;
}
int do_kill(string arg)
{
        object ob,ob2;
        object me = this_player();
        ob2 = this_object();

        if (!arg) return 0;
        ob = present(arg, environment(me));
        if (ob == this_object() || ob == me) return 0;
        if (!ob || !ob->is_character()) return 0;


        if (userp(ob) && ob->query("family/family_name") == "ؤ��") {
                if (me->query("family/family_name") == "ؤ��") {
                message_vision(ob2->name()+"��$N�е������Ȼɱ�Լ���ͬ�ţ��������㣡\n", me);
                kill_ob(me);
                }
                else {
                        message_vision(ob2->name()+"��$N�ȵ����󵨣���Ȼ��������ǰ��Ұ��\n", me);
                        kill_ob(me);
                }
                return 1;
        }
        return 0;
}
