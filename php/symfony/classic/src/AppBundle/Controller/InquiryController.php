<?php

namespace AppBundle\Controller;

use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
use Sensio\Bundle\FrameworkExtraBundle\Configuration\Method;
use Symfony\Component\HttpFoundation\Request;
use AppBundle\Entity\Inquiry;

/**
 * @Route("/inquiry")
 */
class InquiryController extends Controller
{
    /**
     * @Route("/")
     * @Method("get")
     */
    public function IndexAction()
    {
        $form = $this->createInquiryForm();

        return $this->render('Inquiry/index.html.twig', array('form' => $form->createView()));
    }

    /**
     * @Route("/")
     * @Method("post")
     */
    public function IndexPostAction(Request $request)
    {
        $form = $this->createInquiryForm();
        $form->handleRequest($request);
        if ($form->isValid())
        {
            $inquiry = $form->getData();
            $msg = \Swift_Message::newInstance()
                ->setSubject('Webサイトからのお問い合わせ')
                ->setFrom('webmaster@example.com')
                ->setTo('admin@example.com')
                ->setBody($this->renderView('mail/inquiry.txt.twig', array('data' => $inquiry)));

            // $this->get('mailer')->send($msg);

            $em = $this->getDoctrine()->getManager();
            $em->persist($inquiry);
            $em->flush();

            return $this->redirect($this->generateUrl("app_inquiry_complete"));
        }

        return $this->render("Inquiry/index.html.twig", array("form" => $form->createView()));
    }

    /**
     * @Route("/complete")
     */
    public function completeAction()
    {
        return $this->render('Inquiry/complete.html.twig');
    }

    private function createInquiryForm()
    {
        return $this->createFormBuilder(new Inquiry())
        ->add('name', 'text')
        ->add('email', 'text')
        ->add('tel', 'text', ['required' => false,])
        ->add('type', 'choice',
        ['choices' =>
            [
            '公園について',
            'その他',
            ],
            'expanded' => true,
        ])
        ->add('content', 'textarea')
        ->add('submit', 'submit', ['label' => '送信',])
        ->getForm();
    }
}
