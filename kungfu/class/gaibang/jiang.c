// jiang.c ������
// update by looklove 2000,7,3
// Modify By Looklove 2000/10/21
// Modified by looklove 2001/5/24 for xlz quest

inherit NPC;
inherit __DIR__"gb_up.c";
int action_1();
int action_2();
int action_3();
string ask_fenduo();
string ask_zeizi();

void create()
{
        set_name("������", ({"jiang duozhu", "jiang" }));
        set("title", "ؤ��˴�����");
        set("gender", "����");
        set("age", 47);
        set("long",
       		"���ǰ˴��������ƹܴ���ֶ档\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 20);
        set("con", 25);
        set("dex", 25);
        set("unique", 1);

        set("qi", 700);
        set("max_qi", 700);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);

        set("combat_exp", 120000);

        set_skill("force", 100); // �����ڹ�
        set_skill("huntian-qigong", 100); // ��������
        set_skill("strike", 100); // ����ȭ��
        set_skill("blade",90);
        set_skill("liuhe-daofa",90);
        set_skill("dodge", 90); // ��������
        set_skill("xiaoyaoyou", 90); // ǧ������
        set_skill("parry", 90); // �����м�
        set_skill("xianglong-zhang",90);
        map_skill("parry","liuhe-daofa");
        map_skill("strike","xianglong-zhang");
        map_skill("blade","liuhe-daofa");
        map_skill("force", "huntian-qigong");
        map_skill("dodge", "xiaoyaoyou");

        create_family("ؤ��", 19, "�˴�����");
        set("chat_chance", 1);
        set("chat_msg", ({
                "������̾��:�滳����ǰ���ǰ���һ�����Ƶ����Ӱ���\n",
        }) );
        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "����" : (: ask_me :),
                "�ǰ���" : (: action_1 :),
                "�Ⱦ�" : (: action_2 :),
                "С��" : (: action_3 :),
                "�ֶ�����":(: ask_fenduo :),
                "����" : (: ask_zeizi :),
                "����" : (: ask_zeizi :),
                "����" : "��������������Զ���ҵ��ǰ�����\n",
        ]));
        setup();
        carry_object(__DIR__"obj/gb_budai8")->wear();
        carry_object(__DIR__"obj/bainayi")->wear();
        carry_object(BINGQI_D("blade"))->wield();
}

void init()
{
        add_action("do_kill", "kill");
        add_action("do_kill", "tk");
        add_action("do_kill", "teamkill");
        add_action("do_kill", "hit");

        ::init();
        add_action("action_4", "han");
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
                message_vision(ob2->name()+"��$N�е������Ȼɱ�Լ���ͬ�ţ��������㣡"+ob->name()+"���ߣ�\n", me);
                kill_ob(me);
                }
                else {
                        message_vision(ob2->name()+"��$N�ȵ����󵨣���Ȼ��������ǰ��Ұ��"+ob->name()+"���ߣ���������\n", me);
                        kill_ob(me);
                }
                return 1;
        }
        return 0;
}

void dest(object ob)
{
    	if (ob) destruct(ob);
}

int get_object(object ob)
{
        if(userp(ob)) return 1;

        return 0;
}
int accept_object(object who, object ob)
{
    	if (promotion_checking(who,ob)) {
        	call_out("dest", 1, ob);
        	return 1;
    	}
    	return 0;
}

int action_1()
{
        object who = this_player();
        who->set_temp("mark/��1", 1);

        command("say ����ԭ����λ" + RANK_D->query_respect(who) +
                "Ҳ�������ǰ����Ĵ������뵱����������������ǺȾ�" +
                "һ�㶼û�а����ļ��ӡ�");
        return 1;
}

int action_2()
{
        object who = this_player();
        if (!who->query_temp("mark/��1") ) {
                command("say �Ⱦƣ��Ⱦơ�����");
                return 1;
        }
        else {
                who->set_temp("mark/��2", 1);
                command("say ������ԭ��" + RANK_D->query_respect(who) +
                        "Ҳ���������ˣ����꣬������ÿ�춼Ҫ�����Ǻ���һ��" +
                        "�ŵ���Զ����һ��С�������ơ�");
                return 1;
        }
}

int action_3()
{
        object who = this_player();
        if ( !who->query_temp("mark/��2")
	|| who->query("family/family_name") != "ؤ��"
	|| who->query_condition("killer")) {
                command("say ʲôС�����񵺣����ֲ��Ǵ���ġ�");
                return 1;
        }
        else {
                command("say ��λ" + RANK_D->query_respect(who) +
                        "�뵽�ǿ�������ǰ���������ǰ���ȥ�ġ�" +
                        "Ҫȥ��(han)��һ�������ˡ�");
                command("hehehe");
                who->set_temp("mark/��3", 1);
                return 1;
        }
}

int action_4()
{
        object who = this_player();
        object *inv = deep_inventory(who);
        object *obj;
        if ( !who->query_temp("mark/��3") ) {
                command("say û����������ʲô��");
                return 1;
        }
        obj = filter_array(inv,(:get_object:));
        if(sizeof(obj)) {
                command("say �����ϱ�����˭������ô���Ӵ�һ����");
                return 1;
        }
        else {
        command("say �ã�����ʹ���ȥ��");
        message_vision("$N�⿪�����������Ю��$n������ȥ��Ȼ�����" +
                       "һ�ţ��Ͳ����ˡ�\n", this_object(),who);
        who->move("/d/gb/island1");
        tell_object(who,"�������洬�д�����ȥ����һ���������һ�µ��ϡ�\n");
        tell_object(who,"������������˵���������ǰ����������С����\n");
        tell_object(who,"������˵�����ˣ����Ȼ�ȥ���������Լ���һ��ɡ�\n");
        tell_object(who,"��������������˻��֡�\n");
        return 1;
        }
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

        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        command("recruit " + ob->query("id"));
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        ob->set("title",sprintf("ؤ����ŷֶ�%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("gb/fenduo","���ŷֶ�");
        ob->set("gb/alloted",1);
        ob->set("class","beggar");
}
string ask_fenduo()
{
	object me = this_player();
	object ob = this_object();
	int x = me->query("sl_job");

        if ( me->query("family/family_name") != "ؤ��")
                return RANK_D->query_respect(me) + "����ؤ��ú�����֪�˻��Ӻ�̸��";
        if(!me->query_temp("h7g/fenduo"))
        	return "������Ӻ�ƽ����ûʲô���˵��¶���";
        if (me->query_temp("h7g/fenduo")!=1)
        	return "���������ûʲô���飬��л���ġ�";
        if (me->query("h7g/xlz_job")||ob->query("h7g/xlz_jobt"))
                return "���ûʲô���飬��л���ġ�";
        me->set_temp("h7g/xlz_joba",x+1);
        me->set_temp("h7g/xlz_job",1);
        ob->set("h7g/xlz_jobt",me->query("id"));
        return "���ַ���ǰ�����ţ��������������׼�������ɽ�������Ը����㻤�����ִ�ʦǰ����Ԯ����ʮ������Ϊ��";
}
string ask_zeizi()
{
	object me = this_player();
	object ob = this_object();
	int x = me->query("sl_job");
	int y = me->query_temp("h7g/xlz_joba");

        if (!y||(string)ob->query("h7g/xlz_jobt")!=(string)me->query("id"))
        	return "���ַ���ǰ�����ţ��������������׼�������ɽ��";
        if (y<(x+10))
        	return "�����Ը������ս�������ɡ�";

        me->set_temp("h7g/xlz_jobv",1);
        return "�����Ը�������ȥ�ܶ�һ�ˡ�";
}
