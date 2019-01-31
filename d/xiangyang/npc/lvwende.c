// /d/xiangyang/npc/lvwende.c
// by looklove 2000/8/23
inherit NPC;
string ask_me();
void create()
{
        set_name("���ĵ�", ({ "lv wende", "lv" }));
        set("title", "����֪��");
        set("gender", "����");
        set("age", 40);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("long", "��������������֪����������������ξ������ɹ����ӶԿ���\n");
        set("combat_exp", 350000);
        set("attitude", "peaceful");
       set("max_qi", 1200);
       set("max_jing", 1200);
       set("eff_jingli", 1000);
       set("jiali", 30);
       set_skill("force", 70); 
       set_skill("unarmed", 80);
       set_skill("strike", 70);
       set_skill("sword", 70);
       set_skill("dodge", 70);
       set_skill("parry", 70);
       set_skill("qingmang-jian", 80); 
       map_skill("sword", "qingmang-jian");
       map_skill("parry", "qingmang-jian");
       map_skill("parry", "qingmang-jian");
       set("inquiry", ([              
                "����Ͷ��" : (: ask_me :),
                "Ͷ��" : (: ask_me :),
       ]));
        setup();
        carry_object(ARMOR_D("cloth"))->wear();
}

void kill_ob(object ob)
{
//        ob->remove_killer(this_object());
//        remove_killer(ob);
        command("say ɱ��������������");
        ob->add_condition("killer", 5);
        ::kill_ob(ob);
}

int accept_object(object me, object obj)
{            
        int i = me->query("combat_exp")/20000;

        i *= 10000;
        if (i < 200000) i = 200000;
      if(obj->query("money_id")){
        if(me->query("menggu") && me->query_temp("money_ask")){
          if(obj->value() >= i){
              command("haha " + me->query("id"));
              command("whisper "+me->query("id")+" ��ͷ��İɣ�����°��������ϣ�");
                me->delete("menggu");
                me->delete_temp("money_ask");
              return 1;
              }
          else {
              command("say ����ô��Ǯ�ܸ�ʲô��");
              return 1;
              }
          }
        else {
             command("say ����ô��Ǯ�ܸ�ʲô��");
             return 1;
             }
      }
      command("hmm " + me->query("id"));
      command("say �Ҷ�"+obj->name()+"��ϡ����");
      return 0;
}

string ask_me()
{
	object me = this_player();
        int i = me->query("combat_exp")/20000;
    
    if(!me->query("menggu")) return "�Ķ����İ������ң�";
        if (i < 20) i = 20;
    me->set_temp("money_ask", 1);
    message_vision("\n$N����$n������Ц����Ͷ���Ҵ������ǰɣ�\n", this_object(), me);
    command("whisper "+me->query("id")+" "+chinese_number(i)+"���ƽ�");
    return "��֪������ͷ���ɹ��˵�̬�ȡ�����Ҳ�������������ɣ�\n";
}
