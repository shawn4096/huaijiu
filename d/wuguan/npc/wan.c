//wanzhenshan.c 

inherit NPC;

int ask_liguan(); 
void create()
{
        set_name("����ɽ", ({ "wan zhenshan","wan","zhenshan", "guanzhu" }));
        set("title", "������ݹ���");
        set("nickname", "������");
        set("gender", "����");
        set("age", 62);
        set("str", 30);
        set("dex", 26);
        set("long", "�����Ͻ����ӣ�������ϣ�����������վ�����������һ��������\n");
        set("combat_exp", 100000);
        set("shen_type", 1);
        set("attitude", "peaceful");
        set("unique", 1);
         
        set_skill("force", 90);
        set_skill("strike", 90);  
        set_skill("dodge", 90);
        set_skill("parry", 90);     
        set_skill("shenzhao-jing", 90);
        map_skill("force","shenzhao-jing");

        set("inquiry", 
                ([
                        "����" : "�Ǻǣ���ȥ���ҵĴ�ͽ�ܰɣ����ᰲ�����!",
                        "����" : "�������䳡���������ģ���ȥ�Ƕ�����!",
                        "���" : (:ask_liguan:),                        
                ]));

        setup();
        carry_object(ARMOR_D("jinduan"))->wear();
}

int ask_liguan()
{
          object ob;
          ob = this_player();
          if(! ob->query("enter_wuguan")){
            command("say �㲻���Ѿ�����������ô��");
            return 1;
          }
          if(ob ->query("combat_exp") > 3000){          
            command("nod "+ob->query("id"));
            command("say ��λ" + RANK_D->query_respect(ob)+"���Գ�ȥ���������ˣ������ն񣬿�ǧ��С�İ���ȥ����\n"+
                    "��ͽ�����ȥ˵һ���ɣ����ᰲ�ŵġ�");
            ob->delete("enter_wuguan");
            return 1;
          }
          else{
            command("pat "+ob->query("id"));
            command("say ��λ" + RANK_D->query_respect(ob)+"�ľ��黹̫�����̫Σ�գ��㻹�ǹԹ�����������ɡ�");
            return 1;
          }
}
