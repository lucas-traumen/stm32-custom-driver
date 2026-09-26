/* Shared quiz widget for STM32 teach lessons.
   Usage: include after any number of <div class="quiz"> blocks,
   each with .q (prompt), .opt buttons (data-correct on the right one),
   and an optional .feedback container. Options become buttons that
   reveal correct/wrong and unlock the feedback text on a correct pick.
   Every quiz defines a document-wide question counter for numbering. */
(function () {
  var count = 0;
  function bind(quiz) {
    var q = quiz.querySelector('.q');
    if (q) { count++; q.insertAdjacentHTML('beforeend', ' <span class="num">(' + count + ')</span>'); }
    var opts = quiz.querySelectorAll('.opt');
    var fb = quiz.querySelector('.feedback');
    opts.forEach(function (btn) {
      btn.addEventListener('click', function () {
        var correct = btn.hasAttribute('data-correct');
        // clear prior states on this quiz
        opts.forEach(function (o) { o.classList.remove('correct', 'wrong'); });
        btn.classList.add(correct ? 'correct' : 'wrong');
        if (fb) {
          fb.style.color = correct ? '#15803d' : '#b91c1c';
          fb.textContent = correct
            ? 'Đúng! ' + (fb.dataset.good || '')
            : 'Chưa đúng — suy nghĩ lại rồi thử lại.';
        }
      });
    });
  }
  function init() {
    document.querySelectorAll('.quiz').forEach(bind);
  }
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
})();
