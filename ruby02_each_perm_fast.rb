require 'pry'
require 'awesome_print'

def fac(n)
  (1..n).inject(1, &:*)
end

def wife(n, k)
  k = [k, n - 1].min
  result = 0
  n.times.to_a.permutation do |seq|
    i = 0
    best = -1
    while i < k
      best = seq[i] if best < seq[i]
      i += 1
    end
    i += 1 while i < n && seq[i] <= best
    result += 1 if seq[i] == n - 1
  end.sum
  (result.to_f / fac(n)).round(3)
end

def best_wife(n)
  values = n.times.map { |k| wife(n, k) }
  idx = values.index(values.max)
  [n, idx, values[idx], values]
end

def measure
  time_start = Time.now
  result = yield
  time_end = Time.now
  [result, time_end - time_start]
end

(1..10).each do |n|
  p measure { best_wife(n) }
end
