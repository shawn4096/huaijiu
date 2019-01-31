// NPC: song.c �γ���
// Modify By Looklove 2000/10/18

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�γ���", ({"song zhanglao", "song", "zhanglao"}));
	set("title", "ؤ��Ŵ�����");
    	set("nickname", "��������");
	set("gender", "����");
    	set("age", 65);
	set("long", "����ؤ��������֮һ��\n");
	set("attitude", "peaceful");
	set("str", 28);
	set("int", 20);
	set("con", 25);
	set("dex", 28);
	set("apprentice",1);
	set("qi", 1200);
	set("max_qi", 1200);
	set("jing", 600);
	set("max_jing", 600);
	set("neili", 1800);
	set("max_neili", 1800);
	set("jiali", 100);
	
    	set("combat_exp", 550000);
	set("score", 20000);
	
	set_skill("force", 140); // �����ڹ�
	set_skill("huntian-qigong", 140); // ��������
	set_skill("hand", 140); // ����ȭ��
        set_skill("suohou-shou", 140);
	set_skill("dodge", 135); // ��������
        set_skill("xiaoyaoyou", 140); // ǧ������ 
	set_skill("parry", 140); // �����м�
        set_skill("stick", 100);
	set_skill("begging", 100);
	
	map_skill("force", "huntian-qigong");
        map_skill("hand", "suohou-shou");
	map_skill("dodge", "xiaoyaoyou");
	map_skill("parry", "suohou-shou");
	prepare_skill("hand", "suohou-shou");
	
	create_family("ؤ��", 18, "�Ŵ�����");

        set("inquiry", ([
                "ؤ��" : "����ؤ�������µ�һ��\n",
                "����" : "����Ķ���ȥ��\n",
                "���߹�" : "�Ǻǣ���Ҳ��̫�������ȥ��͵���ˡ�\n",
		"�򹷰���" : "�򹷰��˱������֮�����������ǰ���������\n"
			     "��ϧ�ǰ���һȥ�����о���Ҳÿ�˻��ˣ���������\n"
			     "��˵������Ƥ���ճ�һ������������Ǽ������ϣ�\n"
			     "����һ�飬ߥ�����ã���ֻ������һ��㡣\n",
		"ߥ��" : "����ֻ����ƾ��һ���ǰ��������ս����ׯ��ͼ����\n"
			 "ϣ���ܴ�������򹷰��������£�˵������������ \n"
			 "���򲻳�ʲô�򹷰�����������������ֻ����һ��㡣\n",
		"ͼ��" : "������֪�ĸ�������������͵ȥ�ˣ�\n"
        ]));
        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		        }));

	setup();
	carry_object(__DIR__"obj/gb_budai9")->wear();
	carry_object(__DIR__"obj/bainayi")->wear();
}

void attempt_apprentice(object ob)
{
	if ((int)ob->query_str() <=25	) {
		command("say �ҵĹ������ǿ��" + 
		RANK_D->query_respect(ob) + 
		"������̫�����ƺ����ʺϸ���ѧ�书��\n");
		return;
	}

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
        if ((int)ob->query("gb_bags") >= 8 
        && ob->query("family/family_name") == "ؤ��" ) {
                command("say �ҿɲ�����������");
                return;
        }

        command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
        "�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");
        if (ob->query("gb_bags")<1) ob->set("gb_bags", 1);
        command("recruit " + ob->query("id"));
        ob->set("title",sprintf("ؤ���ܶ�%s������",
                chinese_number(ob->query("gb_bags"))) );
        ob->set("class","beggar");
}
