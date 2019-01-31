// guxu.c ����
// Update by caiji@SJ 8/27/2000

inherit NPC;
inherit F_MASTER;

string ask_me();
string ask_for(object);

void create()
{
        set_name("�������", ({ "guxu daozhang", "guxu" }));
        set("long", 
                "�����������۵ĵ��ӹ��������\n"
                "��������ʮ�꣬�����䵱�ɵ����¡�\n");
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        
        set("max_qi", 1500);
        set("max_jing", 800);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("combat_exp", 200000);
        set("score", 8000);

        set_skill("force", 60);
        set_skill("yinyun-ziqi", 70);
        set_skill("dodge", 60);
        set_skill("tiyunzong", 40);
        set_skill("xuanxu-daofa", 100);
        set_skill("blade", 60);
        set_skill("wudang-quan", 100);
        set_skill("parry", 60);
        set_skill("sword", 60);
        set_skill("taoism", 60);
        set_skill("literate", 80);

        map_skill("force", "yinyun-ziqi");
        map_skill("dodge", "tiyunzong");
        map_skill("cuff", "wudang-quan");
        map_skill("parry", "xuanxu-daofa");
        map_skill("blade", "xuanxu-daofa");
        prepare_skill("cuff", "wudang-quan");

        create_family("�䵱��", 3, "����");
        set("class", "taoist");
        
        set("huju_count", 50);

        set("inquiry", 
                ([
                      "���¾�" : (: ask_me :),
                       "huwan" : (: ask_for, "huwan" :),//add by caiji
                        "����" : (: ask_for, "huwan" :),//add by caiji
                        "����" : (: ask_for, "huxiong" :),//add by caiji
                     "huxiong" : (: ask_for, "huxiong" :),//add by caiji
                        "����" : (: ask_for, "huyao" :),//add by caiji
                       "huyao" : (: ask_for, "huyao" :),//add by caiji
                ]));
                                
        set("book_count", 1);

        setup();
        carry_object("/clone/weapon/blade")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

void attempt_apprentice(object ob)
{
        if ((int)ob->query("shen") < 0) {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return;
        }
        command("say �ðɣ�ƶ�����������ˡ�");
        command("recruit " + ob->query("id"));
}

string ask_me()
{
        mapping fam; 
        object ob;

        if (!(fam = this_player()->query("family")) 
            || fam["family_name"] != "�䵱��")
                return RANK_D->query_respect(this_player()) + 
                "�뱾��������������֪�˻��Ӻ�̸��";
        if (query("book_count") < 1)
                return "�������ˣ����ɵĵ����澭���ڴ˴���";
        add("book_count", -1);
        ob = new("/d/wudang/obj/daodejing-ii");
        ob->move(this_player());
        return "�ðɣ��Ȿ�����¾������û�ȥ�ú����С�";
}

string ask_for(string name)
{
        mapping fam; 
        object ob;
        
        if (!(fam = this_player()->query("family")) || fam["family_name"] != "�䵱��")
                return RANK_D->query_respect(this_player()) + 
                "�ֲ����䵱���ӣ��Ҳ����������䵱�ɵĶ�����";

        if (  present(name, this_player()) )
                return RANK_D->query_respect(this_player()) + 
                "���������ϲ�����������������������Ҫ�ˣ� ����̰�����У�";

        if (query("huju_count") < 1)
                return "��Ǹ�������ò���ʱ�����Ѿ������ˣ����´�������ɡ�";

        ob = new("/d/wudang/obj/" + name);
        ob->move(this_player());

        add("huju_count", -1);

        message_vision("$N��$nһ��" + ob->query("name") + "��\n",this_object() ,this_player());

        return "����Ǽ��ö�������Ū���ˡ�";
}
